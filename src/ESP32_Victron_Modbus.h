#pragma once

#include <ModbusIP_ESP8266.h>
#include <WiFi.h>

// You can found a Registry of all available registers in the Victron Modbus documentation:
// https://www.victronenergy.de/upload/documents/CCGX-Modbus-TCP-register-list-3.50.xlsx

// Macro to define the register list using the X-Macro pattern.
// Each entry consists of: Name, Modbus register address, device ID, conversion function, number of decimals.

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
  X(REG_Battery_Temp, 262, 225, convertDiv10, 2) \
  X(REG_Bat_MinCell_Voltage, 1290, 225, convertDiv100, 2) \
  X(REG_Bat_MaxCell_Voltage, 1291, 225, convertDiv100, 2) \
  
  


// Timeout in milliseconds for Modbus transactions.
const int ModbusTimeout = 1000; 

// Typedef for conversion functions that convert a raw uint16_t value to a float.
typedef float (*ConversionFunc)(uint16_t);

// Enum for all register names generated from the REGISTER_LIST macro.
enum RegisterIndex
{
#define X(name, addr, id, conv, decimals) name,
  REGISTER_LIST
#undef X
  REG_COUNT // Automatically counts the number of register entries
};

// Struct that holds detailed information for each register entry.
// Besides the conversion function, it includes the number of decimals for formatting.
struct RegisterEntry
{
  const char *name;         // Name of the register (as a string)
  int address;              // Modbus register address
  uint8_t deviceID;         // Device ID for Modbus communication
  ConversionFunc converter; // Function to convert the raw value
  uint8_t decimals;         // Number of decimals for printing the converted value
};

// Class to manage Modbus communication and register access.
class ModbusManager
{
public:
  // Constructor, takes the remote IP address of the Modbus device.
  ModbusManager(IPAddress remote);
  
  // Initialize the Modbus connection.
  void begin();
  
  // Read all registers defined in REGISTER_LIST.
  void readAllRegisters();
  
  // Get the last read value of a given register by its enum index.
  float getValue(RegisterIndex index) const;
  
  // Read a register's value by its name.
  float readRegisterByName(const char *name);
  
  // Read a register's value by its enum index.
  float readRegister(RegisterIndex index);
  
  // Write a value to a register identified by its enum index.
  bool writeRegister(RegisterIndex index, uint16_t value);

private:
  IPAddress remoteIP;       // Remote IP address of the Modbus device.
  ModbusIP mb;              // Instance of the ModbusIP client.
  
  // Internal array to store the converted register values.
  float regValuesInternal[REG_COUNT];

  // Flag to indicate whether the connection to the Modbus device is active.
  bool isConnected;
  
  // Static array of RegisterEntry, initialized using the REGISTER_LIST macro.
  static const RegisterEntry registers[];

  // Helper function that ensures a connection to the Modbus device is established.
  bool ensureConnected();
};

// Conversion functions to transform raw register data into usable float values.

// No conversion, just cast to float.
static inline float convertNone(uint16_t raw)
{
  return static_cast<float>(raw);
}

// Divide the raw value by 10.
static inline float convertDiv10(uint16_t raw)
{
  return raw / 10.0f;
}

// Divide the raw value by 100.
static inline float convertDiv100(uint16_t raw)
{
  return raw / 100.0f;
}

// Multiply the raw value by 10.
static inline float convertMul10(uint16_t raw)
{
  return raw * 10.0f;
}

// Convert raw data to a signed 16-bit integer and cast to float.
static inline float convertInt16(uint16_t raw)
{
  return static_cast<float>(static_cast<int16_t>(raw));
}

// Convert raw data to a signed 16-bit integer, then divide by 10 for scaling.
static inline float convertInt16Div10(uint16_t raw)
{
  return static_cast<float>(static_cast<int16_t>(raw)) / 10.0f;
}