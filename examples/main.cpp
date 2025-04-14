 

#include <ESP32_Victron_Modbus.h>
#include "RegList.h"
//#include "wpsManager.h" wifi s



//-------------------------------------------------------------------------------//


IPAddress modbusIP(0, 0, 0, 0);
ModbusManager modbus(modbusIP);



void setup()
{
  Serial.begin(115200);
  //start_Wifi();
  modbus.begin();


}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {

    modbus.readAllRegisters(); 
    float minCell = modbus.getValue(REG_Bat_MinCell_Voltage);
    Serial.printf("🔋 CellMin Voltage: %.2f V\n", minCell,2);

   

    

    delay(1000);
  }
}