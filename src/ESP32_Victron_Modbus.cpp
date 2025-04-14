#include "ESP32_Victron_Modbus.h"
#include <Arduino.h>
#include <string.h>

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
  if (!ensureConnected()) return;

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
    regValuesInternal[i] = reg.converter(rawValue);
    // Debug output: print all register name, address, device ID, and formatted value.
    Serial.printf("📟 %s [%d] (ID %d) = %.*f\n", reg.name, reg.address, reg.deviceID, reg.decimals, regValuesInternal[i]);

  }
}

float ModbusManager::getValue(RegisterIndex index) const {
  if (index >= 0 && index < REG_COUNT) return regValuesInternal[index];
  Serial.println("❌ Ungültiger Index");
  return -1;
}

float ModbusManager::readRegister(RegisterIndex index) {
  if (index < 0 || index >= REG_COUNT) {
    Serial.println("❌ Ungültiger Index");
    return -1;
  }

  if (!ensureConnected()) return -1;

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

  regValuesInternal[index] = reg.converter(rawValue);
  return regValuesInternal[index];
}