
#include "ModbusConfig.h"
#include <ESP32_Victron_Modbus.h>
#include "wpsManager.h"


//-------------------------------------------------------------------------------//


IPAddress modbusIP(0, 0, 0, 0);
ModbusManager modbus(modbusIP);



void setup()
{
  Serial.begin(115200);
  start_Wifi();
  modbus.begin();
  //modbus.writeRegister(REG_ESS_MaxPower, 30); // Setze den Wert auf 300
  
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {

    modbus.readAllRegisters(); 
    float minCell = modbus.getValue(REG_Bat_MaxCell_Voltage);
    Serial.printf("🔋 CellMin Voltage: %.2f V\n", minCell,2);

   

    

    delay(1000);
  }
}