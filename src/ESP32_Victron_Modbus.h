#pragma once
#include <ModbusIP_ESP8266.h>
#include <WiFi.h>

#define REGISTER_LIST                                    \
  X(REG_PV1, 811, 100, convertNone, 0)                   \
  X(REG_PV2, 808, 100, convertNone, 0)                   \
  X(REG_OUT_L1, 817, 100, convertNone, 0)                \
  X(REG_OUT_L2, 818, 100, convertNone, 0)                \
  X(REG_OUT_L3, 819, 100, convertNone, 0)                \
  X(REG_BAT_PWR, 842, 100, convertInt16, 1)              \
  X(REG_SOC, 843, 100, convertNone, 0)                   \
  X(REG_minSOC, 2901, 100, convertDiv10, 0)              \
  X(REG_ESS_MaxPower, 2704, 100, convertMul10, 0)        \
  X(REG_MaxCharge, 307, 225, convertDiv10, 1)            \
  X(REG_Battery_Voltage, 259, 225, convertDiv100, 2)     \
  X(REG_Battery_Current, 261, 225, convertInt16Div10, 2) \
  X(REG_Battery_Temp, 262, 225, convertDiv10, 2)



  const int ModbusTimeout = 1000; //  Timeout in Millisekunden


  typedef float (*ConversionFunc)(uint16_t);

// Enum mit allen Registernamen
enum RegisterIndex
{
#define X(name, addr, id, conv, decimals) name,
  REGISTER_LIST
#undef X
      REG_COUNT // Automatisch die Anzahl der Einträge
};

// Erweiterte Struktur der Registereinträge: Zusätzlich zum Converter gibt es jetzt die Anzahl der Nachkommastellen
struct RegisterEntry
{
  const char *name;
  int address;
  uint8_t deviceID;
  ConversionFunc converter;
  uint8_t decimals; // Anzahl der Nachkommastellen für diesen Registerwert
};

class ModbusManager
{
public:
  ModbusManager(IPAddress remote);
  void begin();
  void readAllRegisters();
  float getValue(RegisterIndex index) const;
  float readRegisterByName(const char *name);
  float readRegister(RegisterIndex index);
  bool writeRegister(RegisterIndex index, uint16_t value);

private:
  IPAddress remoteIP;
  ModbusIP mb;
  // Array für die umgerechneten Registerwerte
  float regValuesInternal[REG_COUNT];

  bool isConnected;
  static const RegisterEntry registers[];

  bool ensureConnected(); // Hilfsfunktion, die sicherstellt, dass eine Verbindung besteht.
};

//  Typdefinition für Umrechnungsfunktion:

typedef float (*ConversionFunc)(uint16_t);

static inline float convertNone(uint16_t raw)
{
  return static_cast<float>(raw);
}

static inline float convertDiv10(uint16_t raw)
{
  return raw / 10.0f;
}

static inline float convertDiv100(uint16_t raw)
{
  return raw / 100.0f;
}

static inline float convertMul10(uint16_t raw)
{
  return raw * 10.0f;
}

static inline float convertInt16(uint16_t raw)
{
  return static_cast<float>(static_cast<int16_t>(raw));
}

static inline float convertInt16Div10(uint16_t raw)
{
  return static_cast<float>(static_cast<int16_t>(raw)) / 10.0f;
}
