// ESP32_Victron_Modbus.h
#pragma once

//#include "ModbusConfig.h"  // Eigene Registerliste aus ModbusConfig.h
#include <ModbusIP_ESP8266.h>
#include <WiFi.h>
#include <Arduino.h>
#include <string.h>

// --- Conversion-Funktionen ---
// (alle Funktionen als inline definiert, damit sie in jedem Übersetzungseinheit verfügbar sind)
static inline float convertNone(uint16_t raw) {
  return static_cast<float>(raw);
}

static inline float convertDiv10(uint16_t raw) {
  return raw / 10.0f;
}

static inline float convertDiv100(uint16_t raw) {
  return raw / 100.0f;
}

static inline float convertMul10(uint16_t raw) {
  return raw * 10.0f;
}

static inline float convertInt16(uint16_t raw) {
  return static_cast<float>(static_cast<int16_t>(raw));
}

static inline float convertInt16Div10(uint16_t raw) {
  return static_cast<float>(static_cast<int16_t>(raw)) / 10.0f;
}

// --- Fallback-Definition der REGISTER_LIST, falls sie nicht via ModbusConfig.h definiert wurde ---
#ifndef REGISTER_LIST
#define REGISTER_LIST                                  \
  X(REG_PV1, 811, 100, convertNone, 0)                 \
  X(REG_PV2, 808, 100, convertNone, 0)                 \
  X(REG_OUT_L1, 817, 100, convertNone, 0)              \
  X(REG_OUT_L2, 818, 100, convertNone, 0)              \
  X(REG_OUT_L3, 819, 100, convertNone, 0)              \
  X(REG_BAT_PWR, 842, 100, convertInt16, 1)            \
  X(REG_SOC, 843, 100, convertNone, 0)                 \
  X(REG_minSOC, 2901, 100, convertDiv10, 0)           \
  X(REG_ESS_MaxPower, 2704, 100, convertMul10, 0)      \
  X(REG_MaxCharge, 307, 225, convertDiv10, 1)          \
  X(REG_Battery_Voltage, 259, 225, convertDiv100, 2)   \
  X(REG_Battery_Current, 261, 225, convertInt16Div10, 2)\
  X(REG_Battery_Temp, 262, 225, convertDiv10, 2)       \
  X(REG_Bat_MinCell_Voltage, 1290, 225, convertDiv100, 2)\
  X(REG_Bat_MaxCell_Voltage, 1291, 225, convertDiv100, 2)
#endif

// --- Enum und Strukturen ---
// Enum für Registerindizes, generiert über die REGISTER_LIST
enum RegisterIndex {
#define X(name, addr, id, conv, decimals) name,
  REGISTER_LIST
#undef X
  REG_COUNT // Anzahl der definierten Register
};

// Typdefinition der Konvertierungsfunktion
typedef float (*ConversionFunc)(uint16_t);

// Struktur, die ein Register beschreibt
struct RegisterEntry {
  const char *name;
  int address;
  uint8_t deviceID;
  ConversionFunc converter;
  uint8_t decimals;
};

// Erzeugung des Arrays aus der REGISTER_LIST
#define X(name, addr, id, conv, decimals) { #name, addr, id, conv, decimals },
static const RegisterEntry registers[] = {
  REGISTER_LIST
};
#undef X

// Timeout in Millisekunden für Modbus-Transaktionen
static const int ModbusTimeout = 1000;

// --- Header-only Implementierung der ModbusManager-Klasse ---
class ModbusManager {
public:
  // Konstruktor mit der IP-Adresse des entfernten Geräts
  ModbusManager(IPAddress remote) : remoteIP(remote), isConnected(false) {
    memset(regValuesInternal, 0, sizeof(regValuesInternal));
  }
  
  // Initialisierung: Startet den Modbus Client
  inline void begin() {
    mb.client();
    isConnected = false;
  }
  
  // Liest alle in REGISTER_LIST definierten Register
  inline void readAllRegisters() {
    if (!ensureConnected()) return;
    
    for (int i = 0; i < REG_COUNT; i++) {
      const RegisterEntry &reg = registers[i];
      uint16_t rawValue = 0;
      uint16_t trans = mb.readHreg(remoteIP, reg.address, &rawValue, 1, NULL, reg.deviceID);
      unsigned long start = millis();
      
      while (mb.isTransaction(trans)) {
        mb.task();
        if (millis() - start > ModbusTimeout) {
          Serial.printf("Timeout beim Lesen von %s (Adresse %d)\n", reg.name, reg.address);
          isConnected = false;
          break;
        }
        delay(20);
      }
      regValuesInternal[i] = reg.converter(rawValue);
      Serial.printf("Gelesen: %s [%d] (ID %d) = %.*f\n", reg.name, reg.address, reg.deviceID, reg.decimals, regValuesInternal[i]);
    }
  }
  
  // Liefert den zuletzt gelesenen Wert eines Registers
  inline float getValue(RegisterIndex index) const {
    if(index >= 0 && index < REG_COUNT)
      return regValuesInternal[index];
    Serial.println("Ungültiger Index");
    return -1;
  }
  
  // Liest einen spezifischen Registerwert
  inline float readRegister(RegisterIndex index) {
    if(index < 0 || index >= REG_COUNT) {
      Serial.println("Ungültiger Index");
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
        Serial.printf("Timeout beim Lesen von %s (Adresse %d)\n", reg.name, reg.address);
        isConnected = false;
        return -1;
      }
      delay(20);
    }
    
    regValuesInternal[index] = reg.converter(rawValue);
    return regValuesInternal[index];
  }
  
  // Schreibt einen Wert in ein Register
  inline bool writeRegister(RegisterIndex index, uint16_t value) {
    if(index < 0 || index >= REG_COUNT) {
      Serial.println("Ungültiger Index");
      return false;
    }
    if (!ensureConnected()) return false;
    
    const RegisterEntry &reg = registers[index];
    uint16_t trans = mb.writeHreg(remoteIP, reg.address, &value, 1, NULL, reg.deviceID);
    unsigned long start = millis();
    
    while (mb.isTransaction(trans)) {
      mb.task();
      if (millis() - start > ModbusTimeout) {
        Serial.printf("Timeout beim Schreiben von %s (Adresse %d)\n", reg.name, reg.address);
        isConnected = false;
        return false;
      }
      delay(20);
    }
    Serial.printf("Schreiben erfolgreich: %s (Adresse %d)\n", reg.name, reg.address);
    return true;
  }
  
private:
  // Stellt sicher, dass eine Verbindung besteht
  inline bool ensureConnected() {
    if (!isConnected) {
      if (!mb.connect(remoteIP)) {
        Serial.println("Verbindung konnte nicht hergestellt werden.");
        return false;
      }
      isConnected = true;
    }
    return true;
  }
  
  IPAddress remoteIP;
  ModbusIP mb;
  float regValuesInternal[REG_COUNT];
  bool isConnected;
};
