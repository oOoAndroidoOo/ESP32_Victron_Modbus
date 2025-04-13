# ESP32_Victron_Modbus

Eine Library zur Kommunikation mit Modbus-fähigen Geräten (speziell Victron) über ModbusIP (z. B. mit Solar- oder Batterie-Wechselrichtern).

## Features

- Einfaches Auslesen von Modbus-Registern
- Unterstützt Umrechnungsfunktionen (z. B. /10, *10,  signed/unsigned)
- Automatisierte Registerkonfiguration via Makros
- Debug-Ausgaben über `Serial`

## Voraussetzungen

- ESP8266 oder ESP32
  
-Es wird die modbus-esp8266  von emelianov benötigt
-https://github.com/emelianov/modbus-esp8266.git
