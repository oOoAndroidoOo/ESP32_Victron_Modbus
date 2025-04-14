#include "ESP32_Victron_Modbus.h"
#include <Arduino.h>
#include <string.h>

// Instantiate the static array of RegisterEntry elements using the REGISTER_LIST macro.
// The macro converts each entry into a RegisterEntry struct with the corresponding fields.
#define X(name, addr, id, conv, decimals) { #name, addr, id, conv, decimals },
const RegisterEntry ModbusManager::registers[] = {
    REGISTER_LIST
};
#undef X

// Constructor: initializes the remote IP and resets the connection state and register values.
ModbusManager::ModbusManager(IPAddress remote) : remoteIP(remote), isConnected(false) {
  // Initialize the internal register value array to zero.
  memset(regValuesInternal, 0, sizeof(regValuesInternal));
}

// Begin method: sets up the Modbus client and marks connection as inactive.
void ModbusManager::begin() {
  mb.client();
  isConnected = false;
}

// Helper function to ensure there is an active connection to the Modbus device.
bool ModbusManager::ensureConnected() {
  if (!isConnected) {
    // Attempt to connect to the remote Modbus device.
    if (!mb.connect(remoteIP)) {
      Serial.println("❌ Verbindung konnte nicht hergestellt werden."); // "Connection could not be established."
      return false;
    }
    isConnected = true;
  }
  return true;
}

// Read all registers defined in REGISTER_LIST.
void ModbusManager::readAllRegisters() {
  if (!ensureConnected()) {
    return;
  }

  // Loop through each register entry.
  for (int i = 0; i < REG_COUNT; i++) {
    const RegisterEntry &reg = registers[i];
    uint16_t rawValue = 0;
    
    // Issue a Modbus read holding register command.
    uint16_t trans = mb.readHreg(remoteIP, reg.address, &rawValue, 1, NULL, reg.deviceID);
    unsigned long start = millis();
    
    // Wait until the transaction is complete or until a timeout occurs.
    while (mb.isTransaction(trans)) {
      mb.task();
      if (millis() - start > ModbusTimeout) {
        Serial.printf("⏱️ Timeout beim Lesen von %s (Adresse %d)\n", reg.name, reg.address);
        isConnected = false;
        break;
      }
      delay(20);
    }
    
    // Convert the raw value using the associated conversion function.
    regValuesInternal[i] = reg.converter(rawValue);
    
    // Debug output: print all register name, address, device ID, and formatted value.
    //Serial.printf("📟 %s [%d] (ID %d) = %.*f\n", reg.name, reg.address, reg.deviceID, reg.decimals, regValuesInternal[i]);
  }
}

// Returns the last read value of a register by its index.
float ModbusManager::getValue(RegisterIndex index) const {
  if (index >= 0 && index < REG_COUNT) {
    return regValuesInternal[index];
  } else {
    Serial.println("❌ Ungültiger Index"); // "Invalid index."
    return -1;
  }
}

// Read a single register by its index.
float ModbusManager::readRegister(RegisterIndex index) {
  if (index < 0 || index >= REG_COUNT) {
    Serial.println("❌ Ungültiger Index");
    return -1;
  }

  if (!ensureConnected()) {
    return -1;
  }

  const RegisterEntry &reg = registers[index];
  uint16_t rawValue = 0;
  
  // Issue a read command to the given register.
  uint16_t trans = mb.readHreg(remoteIP, reg.address, &rawValue, 1, NULL, reg.deviceID);
  unsigned long start = millis();
  
  // Wait until the transaction is complete or timeout.
  while (mb.isTransaction(trans)) {
    mb.task();
    if (millis() - start > ModbusTimeout) {
      Serial.printf("⏱️ Timeout beim Lesen von %s (Adresse %d)\n", reg.name, reg.address);
      isConnected = false;
      return -1;
    }
    delay(20);
  }

  // Store and return the converted register value.
  regValuesInternal[index] = reg.converter(rawValue);
  return regValuesInternal[index];
}



// Write a value to a specific register identified by its index.
bool ModbusManager::writeRegister(RegisterIndex index, uint16_t value) {
  if (index < 0 || index >= REG_COUNT) {
    Serial.println("❌ Ungültiger Index");
    return false;
  }

  if (!ensureConnected()) {
    return false;
  }

  const RegisterEntry &reg = registers[index];
  
  // Issue a write command to the register.
  uint16_t trans = mb.writeHreg(remoteIP, reg.address, &value, 1, NULL, reg.deviceID);
  unsigned long start = millis();
  
  // Wait until the write operation completes or a timeout occurs.
  while (mb.isTransaction(trans)) {
    mb.task();
    if (millis() - start > ModbusTimeout) {
      Serial.printf("⏱️ Timeout beim Schreiben von %s (Adresse %d)\n", reg.name, reg.address);
      isConnected = false;
      return false;
    }
    delay(20);
  }

  // Log successful write.
  Serial.printf("✅ Wert von %s (Adresse %d) erfolgreich auf %d gesetzt.\n", reg.name, reg.address, value);
  return true;
}