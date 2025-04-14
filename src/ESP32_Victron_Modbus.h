#pragma once

#include <ModbusIP_ESP8266.h>
#include <WiFi.h>
#include "RegList.h"

// Die Konvertierungsfunktionen sind jetzt als static inline direkt hier deklariert.
// Dadurch sind sie im Header "public" und können vom Benutzer (z. B. in RegList.h) verwendet werden.
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

// Timeout in Millisekunden für Modbus-Transaktionen
const int ModbusTimeout = 1000;

// Typedef für die Umwandlungsfunktionen, die einen rohen uint16_t-Wert in einen float konvertieren.
typedef float (*ConversionFunc)(uint16_t);

// Enum für alle Registerindizes, generiert aus dem REGISTER_LIST Makro.
enum RegisterIndex {
#define X(name, addr, id, conv, decimals) name,
  REGISTER_LIST
#undef X
  REG_COUNT // Zählt automatisch die Anzahl der Register
};

// Struktur, die detaillierte Informationen zu einem Registereintrag hält.
struct RegisterEntry {
  const char *name;         // Name des Registers als String
  int address;              // Modbus Register Adresse
  uint8_t deviceID;         // Device ID für Modbus-Kommunikation
  ConversionFunc converter; // Umwandlungsfunktion
  uint8_t decimals;         // Anzahl der Nachkommastellen
};

class ModbusManager {
public:
  ModbusManager(IPAddress remote);
  
  // Initialisiert die Modbus-Verbindung.
  void begin();
  
  // Liest alle Register, die im REGISTER_LIST definiert sind.
  void readAllRegisters();
  
  // Gibt den zuletzt gelesenen Wert eines Registers zurück.
  float getValue(RegisterIndex index) const;
  
  // Liest einen bestimmten Registerwert.
  float readRegister(RegisterIndex index);
  
  // Schreibt einen Wert in ein Register.
  bool writeRegister(RegisterIndex index, uint16_t value);

private:
  IPAddress remoteIP;   // IP-Adresse des entfernten Modbus-Geräts
  ModbusIP mb;          // Instanz des ModbusIP Clients
  float regValuesInternal[REG_COUNT]; // Internes Array für Registerwerte
  bool isConnected;     // Zustand der Verbindung
  
  // Statische Array-Definition der Register.
  static const RegisterEntry registers[];

  // Hilfsfunktion, um eine Verbindung zum Modbus-Gerät herzustellen.
  bool ensureConnected();
};