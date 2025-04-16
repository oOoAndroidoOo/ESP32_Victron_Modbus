#ifndef REGISTER_LIST
#define REGISTER_LIST                                                                  \
  X(PV_1_L1, 808, 100, convertNone, 0, 1, "W")                                         \
  X(PV_2_L1_out, 811, 100, convertNone, 0, 1, "W")                                     \
  X(AC_Consumption_L1, 817, 100, convertNone, 0, 1, "W")                               \
  X(AC_Consumption_L2, 818, 100, convertNone, 0, 1, "W")                               \
  X(AC_Consumption_L3, 819, 100, convertNone, 0, 1, "W")                               \
  X(Battery_Voltage_System, 840, 100, convertDiv10, 2, 1, "V")                         \
  X(Battery_Current_System, 841, 100, convertInt16Div10, 2, 1, "A")                    \
  X(Battery_Power_System, 842, 100, convertInt16, 2, 1, "W")                           \
  X(Battery_State_of_Charge_System, 843, 100, convertNone, 0, 1, "%")                  \
  X(Battery_State_System, 844, 100, convertNone, 0, 1, "N/A")                          \
  X(VEBus_charge_current_System, 865, 100, convertInt16Div10, 2, 1, "A")               \
  X(VEBus_charge_Power_System, 866, 100, convertInt16, 2, 1, "W")                      \
  X(Input_voltage_phase_1, 3, 228, convertDiv10, 2, 1, "V")                            \
  X(Input_current_phase_1, 6, 228, convertInt16Div10, 2, 1, "A")                       \
  X(Input_frequency_phase_1, 9, 228, convertInt16Div100, 2, 1, "Hz")                   \
  X(Input_power_phase_1, 12, 228, convertInt16, 2, 1, "W")                             \
  X(Output_voltage_phase_1, 15, 228, convertDiv10, 2, 1, "V")                          \
  X(Output_current_phase_1, 18, 228, convertInt16Div10, 2, 1, "A")                     \
  X(Output_frequency_phase_1, 21, 228, convertInt16Div100, 2, 1, "Hz")                 \
  X(Output_power_1, 23, 228, convertInt16Mul10, 2, 1, "W")                             \
  X(Battery_voltage_system, 26, 228, convertDiv100, 2, 1, "V")                         \
  X(Battery_current, 27, 228, convertInt16Div10, 2, 1, "A")                            \
  X(VE_Bus_StateOfCharge, 30, 228, convertDiv10, 0, 1, "%")                            \
  X(Battery_power, 258, 225, convertInt16, 0, 1, "W")                                  \
  X(Battery_voltage, 259, 225, convertDiv100, 2, 1, "V")                               \
  X(Battery_Current, 261, 225, convertInt16Div10, 2, 1, "A")                           \
  X(Battery_Temperature, 262, 225, convertDiv10, 2, 1, "°C")                           \
  X(Battery_State_of_Charge, 266, 225, convertDiv10, 0, 1, "%")                        \
  X(Battery_State_of_Health, 304, 225, convertDiv10, 0, 1, "%")                        \
  X(Batter_Max_charge_voltage, 305, 225, convertDiv10, 1, 1, "V")                      \
  X(Batter_Min_discharge_voltage, 306, 225, convertDiv10, 1, 1, "V")                   \
  X(Batter_Max_charge_current, 307, 225, convertDiv10, 1, 1, "A")                      \
  X(Batter_Max_discharge_current, 308, 225, convertDiv10, 1, 1, "A")                   \
  X(Battery_Minimum_cell_temperature, 318, 225, convertInt16Div10, 1, 1, "°C")         \
  X(Battery_Maximum_cell_temperature, 319, 225, convertInt16Div10, 1, 1, "°C")         \
  X(Battery_Balancing, 1285, 225, convertNone, 0, 1, "N/A")                            \
  X(Battery_Min_cell_voltage, 1290, 225, convertDiv100, 2, 1, "V")                     \
  X(Battery_Max_cell_voltage, 1291, 225, convertDiv100, 2, 1, "V")                     \
  X(Battery_number_of_modules_offline, 1302, 225, convertNone, 0, 1, "N/A")            \
  X(Battery_number_of_modules_online, 1303, 225, convertNone, 0, 1, "N/A")             \
  X(Battery_number_of_modules_blocking_charge, 1304, 225, convertNone, 0, 1, "N/A")    \
  X(Battery_number_of_modules_blocking_discharge, 1305, 225, convertNone, 0, 1, "N/A") \
  X(Grid_L3_Current, 2621, 40, convertInt16Div10, 1, 1, "A")                           \
  X(Grid_AC_Frequency, 2644, 40, convertDiv100, 1, 1, "Hz")
#endif

// ===============================================
//  Inkludierte Libraries und Konvertierungsfunktionen
// ===============================================
#include <ModbusIP_ESP8266.h>
#include <WiFi.h>
#include <Arduino.h>
#include <string.h>

// Optional können in "ModbusConfig.h" alternative Registerlisten definiert werden.
// #include "ModbusConfig.h"

// -----------------------------------------------------------------
// Konvertierungsfunktionen: Verarbeitung des Rohregisters (uint16_t*)
// -----------------------------------------------------------------
typedef float (*ConversionFunc)(const uint16_t *raw);

static inline float convertNone(const uint16_t *raw)
{
  return static_cast<float>(raw[0]);
}

static inline float convertDiv10(const uint16_t *raw)
{
  return raw[0] / 10.0f;
}

static inline float convertDiv100(const uint16_t *raw)
{
  return raw[0] / 100.0f;
}

static inline float convertMul10(const uint16_t *raw)
{
  return raw[0] * 10.0f;
}

static inline float convertSub10(const uint16_t *raw)
{
  return raw[0] - 10.0f;
}

static inline float convertInt16(const uint16_t *raw)
{
  return static_cast<float>(static_cast<int16_t>(raw[0]));
}

static inline float convertInt16Div10(const uint16_t *raw)
{
  return static_cast<float>(static_cast<int16_t>(raw[0])) / 10.0f;
}

static inline float convertInt16Div100(const uint16_t *raw)
{
  return static_cast<float>(static_cast<int16_t>(raw[0])) / 100.0f;
}

static inline float convertInt16Mul10(const uint16_t *raw)
{
  return static_cast<float>(static_cast<int16_t>(raw[0])) * 10.0f;
}

static inline float convertInt32(const uint16_t *raw)
{
  uint32_t value = (static_cast<uint32_t>(raw[0]) << 16) | raw[1];
  return static_cast<float>(value);
}

static inline float convertInt32Div10(const uint16_t *raw)
{
  uint32_t value = (static_cast<uint32_t>(raw[0]) << 16) | raw[1];
  return static_cast<float>(value) / 10.0f;
}

static inline float convertInt32Div100(const uint16_t *raw)
{
  uint32_t value = (static_cast<uint32_t>(raw[0]) << 16) | raw[1];
  return static_cast<float>(value) / 100.0f;
}

// ===============================================
//  Datenstrukturen: RegisterEntry, Enum und Array-Erzeugung
// ===============================================
struct RegisterEntry
{
  const char *name;
  int address;
  uint8_t deviceID;
  ConversionFunc converter;
  uint8_t decimals;
  uint8_t wordCount; // 1 = 16-Bit, 2 = 32-Bit Register
  const char *unit;  // NEUES Feld für Einheit
};

// Erzeugung des Enums mittels REGISTER_LIST
enum RegisterIndex
{
#define X(name, addr, id, conv, decimals, words, unit) name,
  REGISTER_LIST
#undef X
      REG_COUNT // Anzahl definierter Register
};

// Erzeugung des Arrays aller Register-Einträge
static const RegisterEntry registers[] = {
#define X(name, addr, id, conv, decimals, words, unit) {#name, addr, id, conv, decimals, words, unit},
    REGISTER_LIST
#undef X
};

// Timeout in Millisekunden für Modbus-Transaktionen
static const int ModbusTimeout = 1000;

// ===============================================
// 4. Die ModbusManager-Klasse
// ===============================================
class ModbusManager
{
public:
  // Konstruktor: Initialisiert den Manager mit der IP des entfernten Geräts.
  ModbusManager(IPAddress remote) : remoteIP(remote), isConnected(false)
  {
    memset(regValuesInternal, 0, sizeof(regValuesInternal));
  }
  void setDebug(bool enable)
  { // Enables or disables debug output
    debugMode = enable;
  }
  // Initialisierung: Startet den Modbus-Client.
  inline void begin()
  {
    mb.client();
    isConnected = false;
  }

  // Liest alle in REGISTER_LIST definierten Register.
  inline void readAllRegisters()
  {
    if (!ensureConnected())
      return;

    for (int i = 0; i < REG_COUNT; i++)
    {
      const RegisterEntry &reg = registers[i];
      uint16_t raw[2] = {0, 0}; // Puffer, unterstützt 1 oder 2 WORDS
      uint16_t trans = mb.readHreg(remoteIP, reg.address, raw, reg.wordCount, NULL, reg.deviceID);
      unsigned long start = millis();

      while (mb.isTransaction(trans))
      {
        mb.task();
        if (millis() - start > ModbusTimeout)
        {
          Serial.printf("Timeout beim Lesen von %s (Adresse %d)\n", reg.name, reg.address);
          isConnected = false;
          break;
        }
        delay(20);
      }
      regValuesInternal[i] = reg.converter(raw);
      if (debugMode)
        Serial.printf("Gelesen: %s [%d] (ID %d) = %.*f %s\n",
                      reg.name, reg.address, reg.deviceID, reg.decimals, regValuesInternal[i], reg.unit);
    }
  }

  // Liefert den zuletzt gelesenen Wert eines spezifischen Registers.
  inline float getValue(RegisterIndex index) const
  {
    if (index >= 0 && index < REG_COUNT)
      return regValuesInternal[index];
    Serial.println("Ungültiger Index");
    return -1;
  }

  // Liest gezielt einen Registerwert.
  inline float readRegister(RegisterIndex index)
  {
    if (index < 0 || index >= REG_COUNT)
    {
      Serial.println("Ungültiger Index");
      return -1;
    }
    if (!ensureConnected())
      return -1;

    const RegisterEntry &reg = registers[index];
    uint16_t raw[2] = {0, 0};
    uint16_t trans = mb.readHreg(remoteIP, reg.address, raw, reg.wordCount, NULL, reg.deviceID);
    unsigned long start = millis();

    while (mb.isTransaction(trans))
    {
      mb.task();
      if (millis() - start > ModbusTimeout)
      {
        Serial.printf("Timeout beim Lesen von %s (Adresse %d)\n", reg.name, reg.address);
        isConnected = false;
        return -1;
      }
      delay(20);
    }
    regValuesInternal[index] = reg.converter(raw);
    if (debugMode)
      Serial.printf("Gelesen: %s [%d] (ID %d) = %.*f %s\n",
                    reg.name, reg.address, reg.deviceID, reg.decimals, regValuesInternal[index], reg.unit);
    return regValuesInternal[index];
  }

  // Schreibt einen Wert in ein Register (nur für 16-Bit Register geeignet).
  inline bool writeRegister(RegisterIndex index, uint16_t value)
  {
    if (index < 0 || index >= REG_COUNT)
    {
      Serial.println("Ungültiger Index");
      return false;
    }
    if (!ensureConnected())
      return false;

    const RegisterEntry &reg = registers[index];
    if (reg.wordCount != 1)
    {
      if (debugMode)
        Serial.println("Schreiben für 32-Bit Register nicht unterstützt.");
      return false;
    }

    uint16_t trans = mb.writeHreg(remoteIP, reg.address, &value, 1, NULL, reg.deviceID);
    unsigned long start = millis();

    while (mb.isTransaction(trans))
    {
      mb.task();
      if (millis() - start > ModbusTimeout)
      {
        Serial.printf("Timeout beim Schreiben von %s (Adresse %d)\n", reg.name, reg.address);
        isConnected = false;
        return false;
      }
      delay(20);
    }
    if (debugMode)
    Serial.printf("Schreiben erfolgreich: %s (Adresse %d)\n", reg.name, reg.address);
    return true;
  }

  // ===============================================
  // Formatierte Ausgabe des Registerwerts als String (z. B. "12.34 V")
  // ===============================================
  String getFormattedValue(RegisterIndex index) const
  {
    if (index >= 0 && index < REG_COUNT)
    {
      const RegisterEntry &reg = registers[index];
      char buffer[32];
      snprintf(buffer, sizeof(buffer), "%.*f %s", reg.decimals, regValuesInternal[index], reg.unit);
      return String(buffer);
    }
    return "Ungültiger Index";
  }

private:
  // Stellt sicher, dass eine Verbindung besteht.
  inline bool ensureConnected()
  {
    if (!isConnected)
    {
      if (!mb.connect(remoteIP))
      {
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
  bool debugMode; // Debug flag to control debug output
};