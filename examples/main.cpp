#include "ESP32_Victron_Modbus.h"

// #include "wpsManager.h"  anything to Connect to WiFi




IPAddress modbusIP(0, 0, 0, 0);

ModbusManager modbus(modbusIP);



void setup() {
  Serial.begin(115200);
  //start_Wifi();

  modbus.begin();


}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
   
  //  modbus.readAllRegisters(); // bei Bedarf aktivieren
   modbus.readAllRegisters();
   
   Serial.println(modbus.getValue(REG_BAT_PWR));
  // int socValue = modbus.readRegisterByName(REG_SOC);
  Serial.printf("🔋 BatterieLeistung      : %.2f W\n", modbus.readRegister(REG_BAT_PWR));
  Serial.printf("🔋 Batteriespannung      : %.2f V\n", modbus.readRegister(REG_Battery_Voltage));
  Serial.printf("🔋 Batteriestrom         : %.2f A\n", modbus.readRegister(REG_Battery_Current));
  Serial.printf("🔋 BatterieTemperatur    : %.2f C\n", modbus.readRegister(REG_Battery_Temp));

 // Serial.println(modbus.readRegister(REG_Battery_Voltage));
 // Serial.printf("🔋 Batter Strom     : %d\n",modbus.readRegister(REG_Battery_Current));
 // Serial.printf("🔋 Batter Temperatur: %d°C\n",modbus.readRegister(REG_Battery_Temp)/10);
  
   
    delay(10000);
  }
}