
#include "ModbusConfig.h" 
// #include "ModbusManager.h" its Important for the ModbusManager to work with your own ModbusConfig.h file
// this file must be first included in the main.cpp file

#include <ESP32_Victron_Modbus.h>
#include "wpsManager.h" 


//-------------------------------------------------------------------------------//


IPAddress modbusIP(192, 168, 177, 240); //Your Modbus device IP address
ModbusManager modbus(modbusIP); // ModbusManager instance with the IP address of the Modbus device



void setup()
{
  Serial.begin(115200);   // Initialize Serial Monitor for debugging
  start_Wifi();           // Start WiFi connection 
 
  modbus.begin();         // Initialize Modbus connection
  modbus.setDebug(false); // Enable debug messages for Modbus communication

}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {

    // Read all registers defined in REGISTER_LIST
  modbus.readAllRegisters();

  // Example: Retrieve Battery Voltage and Battery Current from the registers.
  // The following register names are defined in your REGISTER_LIST.
  float batteryVoltage = modbus.getValue(Battery_voltage);   // e.g. Conversion: raw/10.0 -> Voltage in V
  float batteryCurrent = modbus.getValue(Battery_current);   // e.g. Conversion: raw/10.0 -> Current in A

  // Formatted output using your getFormattedValue() method.
  Serial.println("----- Modbus Register Values -----");
  Serial.print("Battery Voltage: ");
  Serial.println(modbus.getFormattedValue(Battery_voltage));  // e.g. "12.75 V"
  Serial.print("Battery Current: ");
  Serial.println(modbus.getFormattedValue(Battery_current));  // e.g. "2.5 A"
  Serial.print("Battery Power (from register): ");
  Serial.println(modbus.getFormattedValue(Battery_power));      // Already calculated in register
  Serial.println("----------------------------------");

  // Arithmetic example: Calculate estimated power if not provided directly.
  // Multiplying voltage and current (make sure to use converted values!)
  float estimatedPower = batteryVoltage * batteryCurrent;
  Serial.printf("Estimated Power (V * I): %.2f W\n", estimatedPower);

  // Additional example: Calculation involving Grid energy.
  // Using Grid_Total_Energy_from_net and Grid_Total_Energy_to_net registers to compute a net energy value.
  float energyFromNet = modbus.getValue(Grid_Total_Energy_from_net);  // Unit: kWh, based on conversion
  float energyToNet   = modbus.getValue(Grid_Total_Energy_to_net);    // Unit: kWh, based on conversion
  float netEnergy     = energyFromNet - energyToNet;
  Serial.printf("Net Energy from Grid: %.2f kWh\n", netEnergy);

  // Example: Writing a value to a register.
  // Note: writeRegister() is only supported for 16-bit registers.
  // Here we attempt to write to the first register "System_PV_AC_coupled_on_output_L1".
  //  modbus.writeRegister(ARegistertowrite, 500); // 500 is an example value.
delay(1000); 
  }
 
  }
  



   
   

    

