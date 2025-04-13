#include "ESP32_Victron_Modbus.h"
#include <Arduino.h>
#include <string.h>

// Initialisierung des statischen Arrays für Registereinträge, inklusive des neuen "decimals"-Feldes.
#define X(name, addr, id, conv, decimals) { #name, addr, id, conv, decimals },
const RegisterEntry ModbusManager::registers[] = {
    REGISTER_LIST
};
#undef X

ModbusManager::ModbusManager(IPAddress remote) : remoteIP(remote), isConnected(false) {
  memset(regValuesInternal, 0, sizeof(regValuesInternal));
}

void ModbusManager::begin() {
  mb.client();
  isConnected = false;
}

bool ModbusManager::ensureConnected() {
  if (!isConnected) {
    if (!mb.connect(remoteIP)) {
      Serial.println("❌ Verbindung konnte nicht hergestellt werden.");
      return false;
    }
    isConnected = true;
  }
  return true;
}

void ModbusManager::readAllRegisters() {
  if (!ensureConnected()) {
    return;
  }

  for (int i = 0; i < REG_COUNT; i++) {
    const RegisterEntry &reg = registers[i];
    uint16_t rawValue = 0;
    uint16_t trans = mb.readHreg(remoteIP, reg.address, &rawValue, 1, NULL, reg.deviceID);
    unsigned long start = millis();
    while (mb.isTransaction(trans)) {
      mb.task();
      if (millis() - start > ModbusTimeout) {
        Serial.printf("⏱️ Timeout beim Lesen von %s (Adresse %d)\n", reg.name, reg.address);
        isConnected = false;
        break;
      }
      delay(20);
    }
    // Hier wird der rohe Wert mithilfe der Umrechnungsfunktion transformiert.
    regValuesInternal[i] = reg.converter(rawValue);
    // Optional: Debug-Ausgabe, z.B. mit der angegebenen Nachkommastellen-Präzision:
 Serial.printf("📟 %s [%d] (ID %d) = %.*f\n", reg.name, reg.address, reg.deviceID, reg.decimals, regValuesInternal[i]);
  }
}

float ModbusManager::getValue(RegisterIndex index) const {
  if (index >= 0 && index < REG_COUNT) {
    return regValuesInternal[index];
  } else {
    Serial.println("❌ Ungültiger Index");
    return -1;
  }
}

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
  uint16_t trans = mb.readHreg(remoteIP, reg.address, &rawValue, 1, NULL, reg.deviceID);
  unsigned long start = millis();
  while (mb.isTransaction(trans)) {
    mb.task();
    if (millis() - start > ModbusTimeout) {
      Serial.printf("⏱️ Timeout beim Lesen von %s (Adresse %d)\n", reg.name, reg.address);
      isConnected = false;
      return -1;
    }
    delay(20);
  }

  // Umrechnung: Anwendung der konfigurierten Umrechnungsfunktion
  regValuesInternal[index] = reg.converter(rawValue);
  return regValuesInternal[index];
}

float ModbusManager::readRegisterByName(const char *name) {
  const RegisterEntry *found = nullptr;
  for (int i = 0; i < REG_COUNT; i++) {
    if (strcmp(registers[i].name, name) == 0) {
      found = &registers[i];
      break;
    }
  }
  if (!found) {
    Serial.printf("⚠️ Register nicht gefunden: %s\n", name);
    return -1;
  }
  
  if (!ensureConnected()) {
    return -1;
  }

  uint16_t rawValue = 0;
  uint16_t trans = mb.readHreg(remoteIP, found->address, &rawValue, 1, NULL, found->deviceID);
  unsigned long start = millis();
  while (mb.isTransaction(trans)) {
    mb.task();
    if (millis() - start > ModbusTimeout) {
      Serial.printf("⏱️ Timeout beim Lesen von %s (Adresse %d)\n", found->name, found->address);
      isConnected = false;
      return -1;
    }
    delay(20);
  }
  
  return found->converter(rawValue);
}

bool ModbusManager::writeRegister(RegisterIndex index, uint16_t value) {
  if (index < 0 || index >= REG_COUNT) {
    Serial.println("❌ Ungültiger Index");
    return false;
  }

  if (!ensureConnected()) {
    return false;
  }

  const RegisterEntry &reg = registers[index];
  
  uint16_t trans = mb.writeHreg(remoteIP, reg.address, &value, 1, NULL, reg.deviceID);
  unsigned long start = millis();
  while (mb.isTransaction(trans)) {
    mb.task();
    if (millis() - start > ModbusTimeout) {
      Serial.printf("⏱️ Timeout beim Schreiben von %s (Adresse %d)\n", reg.name, reg.address);
      isConnected = false;
      return false;
    }
    delay(20);
  }

  Serial.printf("✅ Wert von %s (Adresse %d) erfolgreich auf %d gesetzt.\n", reg.name, reg.address, value);
  return true;
}
