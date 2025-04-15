#pragma once

// ===============================================
// 1. Erweiterte REGISTER_LIST Definition
// ===============================================
// Hier definieren wir die Registerliste mit Name, Adresse, deviceID,
// Konvertierungsfunktion, Dezimalstellen, wordCount und Einheit.
#define REGISTER_LIST                                                               \
  X(PV_AC_coupled_on_output_L1, 808, 100, convertNone, 0, 1, "W")                   \
  X(PV_AC_coupled_on_input_L1, 811, 100, convertNone, 0, 1, "W")                    \
  X(AC_Consumption_L1, 817, 100, convertNone, 0, 1, "W")                            \
  X(AC_Consumption_L2, 818, 100, convertNone, 0, 1, "W")                            \
  X(AC_Consumption_L3, 819, 100, convertNone, 0, 1, "W")                            \
  X(Battery_Voltage_System, 840, 100, convertDiv10, 2, 1, "V")                      \
  X(Battery_Current_System, 841, 100, convertInt16Div10, 2, 1, "A")                 \
  X(Battery_Power_System, 842, 100, convertInt16, 2, 1, "W")                        \
  X(Battery_State_of_Charge_System, 843, 100, convertNone, 0, 1, "%")               \
  X(Battery_State_System, 844, 100, convertNone, 0, 1, "")                          \
  X(VEBus_charge_current_System, 865, 100, convertInt16Div10, 2, 1, "A")            \
  X(VEBus_charge_Power_System, 866, 100, convertInt16, 2, 1, "W")                   \
  X(Input_voltage_phase_1, 3, 228, convertDiv10, 2, 1, "V")                         \
  X(Input_current_phase_1, 6, 228, convertInt16Div10, 2, 1, "A")                    \
  X(Input_frequency_phase_1, 9, 228, convertInt16Div100, 2, 1, "Hz")                \
  X(Input_power_phase_1, 12, 228, convertInt16, 2, 1, "W")                          \
  X(Output_voltage_phase_1, 15, 228, convertDiv10, 2, 1, "V")                       \
  X(Output_current_phase_1, 18, 228, convertInt16Div10, 2, 1, "A")                  \
  X(Output_frequency_phase_1, 21, 228, convertInt16Div100, 2, 1, "Hz")              \
  X(Output_power_1, 23, 228, convertInt16Mul10, 2, 1, "W")                          \
  X(Battery_voltage_system, 26, 228, convertDiv100, 2, 1, "V")                      \
  X(Battery_current, 27, 228, convertInt16Div10, 2, 1, "A")                         \
  X(VE_Bus_StateOfCharge, 30, 228, convertDiv10, 0, 1, "%")                         \
  X(Battery_power, 258, 225, convertInt16, 0, 1, "W")                               \
  X(Battery_voltage, 259, 225, convertDiv100, 2, 1, "V")                            \
  X(Battery_Current, 261, 225, convertInt16Div10, 2, 1, "A")                        \
  X(Battery_Temperature, 262, 225, convertDiv10, 2, 1, "°C")                        \
  X(Battery_State_of_Charge, 266, 225, convertDiv10, 0, 1, "%")                     \
  X(Battery_State_of_Health, 304, 225, convertDiv10, 0, 1, "%")                     \
  X(Batter_Max_charge_voltage, 305, 225, convertDiv10, 1, 1, "V")                   \
  X(Batter_Min_discharge_voltage, 306, 225, convertDiv10, 1, 1, "V")                \
  X(Batter_Max_charge_current, 307, 225, convertDiv10, 1, 1, "A")                   \
  X(Batter_Max_discharge_current, 308, 225, convertDiv10, 1, 1, "A")                \
  X(Battery_Minimum_cell_temperature, 318, 225, convertInt16Div10, 1, 1, "°C")      \
  X(Battery_Maximum_cell_temperature, 319, 225, convertInt16Div10, 1, 1, "°C")      \
  X(Battery_Balancing, 1285, 225, convertNone, 0, 1, "")                            \
  X(Battery_Min_cell_voltage, 1290, 225, convertDiv100, 2, 1, "V")                  \
  X(Battery_Max_cell_voltage, 1291, 225, convertDiv100, 2, 1, "V")                  \
  X(Battery_number_of_modules_offline, 1302, 225, convertNone, 0, 1, "")            \
  X(Battery_number_of_modules_online, 1303, 225, convertNone, 0, 1, "")             \
  X(Battery_number_of_modules_blocking_charge, 1304, 225, convertNone, 0, 1, "")    \
  X(Battery_number_of_modules_blocking_discharge, 1305, 225, convertNone, 0, 1, "") \
  X(Grid_L3_Current, 2621, 40, convertInt16Div10, 1, 1, "A")                        \
  X(Grid_AC_Frequency, 2644, 40, convertDiv100, 1, 1, "Hz")                         \
  X(Grid_Total_Energy_from_net, 2634, 40, convertInt32Div100, 2, 2, "kWh")          \
  X(Grid_Total_Energy_to_net, 2636, 40, convertInt32Div100, 2, 2, "kWh")
  
