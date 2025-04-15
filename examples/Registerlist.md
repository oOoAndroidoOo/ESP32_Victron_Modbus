
# Here is a list of some registers (mainly registers for a Victron Multiplus GX).
  This list is incomplete.

A complete list of all registers can be found here:
https://www.victronenergy.de/support-and-downloads/technical-information

 Caution! Many of the registers also have write permissions.
 Only write to registers if you know exactly what you are doing.
 I assume no responsibility for any resulting damage.


The register names used here are freely selectable and are only used for comparison with the Victron register list.

 For example, you can also assign your own Registername or unit of measurement for:
X(System_PV_AC_coupled_on_output_L1, 808, 100, convertNone, 0, 1,"W")

 You can also assign a custom Registername. e.g.:
X(MyRegiser, 808, 100, convertNone, 0, 1, ,"Mymeasurement")


 Please note that depending on the configuration of the Victron devices, not all registers contain data

#define REGISTER_LIST                                             \
  X(System_PV_AC_coupled_on_output_L1, 808, 100, convertNone, 0, 1, "W")         \
  X(System_PV_AC_coupled_on_output_L2, 809, 100, convertNone, 0, 1, "W")         \
  X(System_PV_AC_coupled_on_output_L3, 810, 100, convertNone, 0, 1, "W")         \
  X(System_PV_AC_coupled_on_input_L1, 811, 100, convertNone, 0, 1, "W")          \
  X(System_PV_AC_coupled_on_input_L2, 812, 100, convertNone, 0, 1, "W")          \
  X(System_PV_AC_coupled_on_input_L3, 813, 100, convertNone, 0, 1, "W")          \
  X(System_PV_AC_coupled_on_generator_L1, 814, 100, convertNone, 0, 1, "W")      \
  X(System_PV_AC_coupled_on_generator_L2, 815, 100, convertNone, 0, 1, "W")      \
  X(System_PV_AC_coupled_on_generator_L3, 816, 100, convertNone, 0, 1, "W")      \
  X(System_AC_Consumption_L1, 817, 100, convertNone, 0, 1, "W")                  \
  X(System_AC_Consumption_L2, 818, 100, convertNone, 0, 1, "W")                  \
  X(System_AC_Consumption_L3, 819, 100, convertNone, 0, 1, "W")                  \
  X(System_Grid_L1, 820, 100, convertInt16, 0, 1, "W")                           \
  X(System_Grid_L2, 821, 100, convertInt16, 0, 1, "W")                           \
  X(System_Grid_L3, 822, 100, convertInt16, 0, 1, "W")                           \
  X(System_Genset_L1, 823, 100, convertInt16, 0, 1, "W")                         \
  X(System_Genset_L2, 824, 100, convertInt16, 0, 1, "W")                         \
  X(System_Genset_L3, 825, 100, convertInt16, 0, 1, "W")                         \
  X(System_Active_input_source, 826, 100, convertInt16, 0, 1, "")                \
  X(System_Battery_Voltage, 840, 100, convertDiv10, 2, 1, "V")                   \
  X(System_Battery_Current, 841, 100, convertInt16Div10, 2, 1, "A")              \
  X(System_Battery_Power, 842, 100, convertInt16, 2, 1, "W")                     \
  X(System_Battery_State_of_Charge, 843, 100, convertNone, 0, 1, "%")            \
  X(System_Battery_State, 844, 100, convertNone, 0, 1, "")                       \
  X(System_charge_current, 865, 100, convertInt16Div10, 2, 1, "A")               \
  X(System_charge_Power, 866, 100, convertInt16, 2, 1, "W")                      \
  X(System_PowerOnOutputOfInverterCharger_L1, 878, 100, convertInt32, 0, 2, "W") \
  X(System_Inverter_Charger_Power, 870, 100, convertInt32, 0, 2, "W")            \
  X(VE_Bus_Input_voltage_phase_1, 3, 228, convertDiv10, 2, 1, "V")               \
  X(VE_Bus_Input_voltage_phase_2, 4, 228, convertDiv10, 2, 1, "V")               \
  X(VE_Bus_Input_voltage_phase_3, 5, 228, convertDiv10, 2, 1, "V")               \
  X(VE_Bus_Input_current_phase_1, 6, 228, convertInt16Div10, 2, 1, "A")          \
  X(VE_Bus_Input_current_phase_2, 7, 228, convertInt16Div10, 2, 1, "A")          \
  X(VE_Bus_Input_current_phase_3, 8, 228, convertInt16Div10, 2, 1, "A")          \
  X(VE_Bus_Input_frequency_phase_1, 9, 228, convertInt16Div100, 2, 1, "Hz")      \
  X(VE_Bus_Input_frequency_phase_2, 10, 228, convertInt16Div100, 2, 1, "Hz")     \
  X(VE_Bus_Input_frequency_phase_3, 11, 228, convertInt16Div100, 2, 1, "Hz")     \
  X(VE_Bus_Input_power_phase_1, 12, 228, convertInt16, 2, 1, "W")                \
  X(VE_Bus_Input_power_phase_2, 13, 228, convertInt16, 2, 1, "W")                \
  X(VE_Bus_Input_power_phase_3, 14, 228, convertInt16, 2, 1, "W")                \
  X(VE_Bus_Output_voltage_phase_1, 15, 228, convertDiv10, 2, 1, "V")             \
  X(VE_Bus_Output_voltage_phase_2, 16, 228, convertDiv10, 2, 1, "V")             \
  X(VE_Bus_Output_voltage_phase_3, 17, 228, convertDiv10, 2, 1, "V")             \
  X(VE_Bus_Output_current_phase_1, 18, 228, convertInt16Div10, 2, 1, "A")        \
  X(VE_Bus_Output_current_phase_2, 19, 228, convertInt16Div10, 2, 1, "A")        \
  X(VE_Bus_Output_current_phase_3, 20, 228, convertInt16Div10, 2, 1, "A")        \
  X(VE_Bus_Output_frequency_phase_1, 21, 228, convertInt16Div100, 2, 1, "Hz")    \
  X(VE_Bus_Active_input_current_limit, 22, 228, convertInt16Div10, 2, 1, "A")    \
  X(VE_Bus_Output_power_1, 23, 228, convertInt16Mul10, 2, 1, "W")                \
  X(VE_Bus_Output_power_2, 24, 228, convertInt16Mul10, 2, 1, "W")                \
  X(VE_Bus_Output_power_3, 25, 228, convertInt16Mul10, 2, 1, "W")                \
  X(VE_Bus_Battery_voltage_system, 26, 228, convertDiv100, 2, 1, "V")            \
  X(VE_Bus_Battery_current_system, 27, 228, convertInt16Div10, 2, 1, "A")        \
  X(VE_Bus_Phase_count, 28, 228, convertNone, 0, 1, "")                          \
  X(VE_Bus_Active_input, 29, 228, convertNone, 0, 1, "")                         \
  X(VE_Bus_StateOfCharge, 30, 228, convertDiv10, 0, 1, "%")                      \
  X(VE_Bus_State, 31, 228, convertNone, 0, 1, "")                                \
  X(VE_Bus_Error, 32, 228, convertNone, 0, 1, "")                                \
  X(VE_Bus_Switch_position, 33, 228, convertNone, 0, 1, "")                      \
  X(VE_Bus_Temperature_alarm, 34, 228, convertNone, 0, 1, "")                    \
  X(VE_Bus_Low_Battery_alarm, 35, 228, convertNone, 0, 1, "")                    \
  X(VE_Bus_Overload_alarm, 36, 228, convertNone, 0, 1, "")                       \
  X(VE_Bus_ESS_power_setpoint_phase1, 37, 228, convertInt16, 0, 1, "W")          \
  X(VE_Bus_ESS_disable_charge_flag_phase, 38, 228, convertNone, 0, 1, "")        \
  X(VE_Bus_ESS_disable_feedback_flag_phase, 39, 228, convertNone, 0, 1, "")      \
  X(VE_Bus_ESS_power_setpoint_phase2, 40, 228, convertInt16, 0, 1, "W")          \
  X(VE_Bus_ESS_power_setpoint_phase3, 41, 228, convertInt16, 0, 1, "W")          \
  X(VE_Bus_Temperatur_sensor_alarm, 42, 228, convertNone, 0, 1, "")              \
  X(VE_Bus_Voltage_sensor_alarm, 43, 228, convertNone, 0, 1, "")                 \
  X(VE_Bus_Temperature_alarm_L1, 44, 228, convertNone, 0, 1, "")                 \
  X(VE_Bus_Low_battery_alarm_L1, 45, 228, convertNone, 0, 1, "")                 \
  X(VE_Bus_Overload_alarm_L1, 46, 228, convertNone, 0, 1, "")                    \
  X(VE_Bus_Ripple_alarm_L1, 47, 228, convertNone, 0, 1, "")                      \
  X(VE_Bus_Temperature_alarm_L2, 48, 228, convertNone, 0, 1, "")                 \
  X(VE_Bus_Low_battery_alarm_L2, 49, 228, convertNone, 0, 1, "")                 \
  X(VE_Bus_Overload_alarm_L2, 50, 228, convertNone, 0, 1, "")                    \
  X(VE_Bus_Ripple_alarm_L2, 51, 228, convertNone, 0, 1, "")                      \
  X(VE_Bus_Temperature_alarm_L3, 52, 228, convertNone, 0, 1, "")                 \
  X(VE_Bus_Low_battery_alarm_L3, 53, 228, convertNone, 0, 1, "")                 \
  X(VE_Bus_Overload_alarm_L3, 54, 228, convertNone, 0, 1, "")                    \
  X(VE_Bus_Ripple_alarm_L3, 55, 228, convertNone, 0, 1, "")                      \
  X(VE_Bus_Disable_PV_inverter, 56, 228, convertNone, 0, 1, "")                  \
  X(VEBus_BMSallowsbatterytobecharged, 57, 228, convertNone, 0, 1, "")           \
  X(VEBus_BMSallowsbatterytobedischarged, 58, 228, convertNone, 0, 1, "")        \
  X(VEBus_BMSisexpected, 59, 228, convertNone, 0, 1, "")                         \
  X(VEBus_BMSerror, 60, 228, convertNone, 0, 1, "")                              \
  X(VE_Bus_Battery_temperature, 61, 228, convertInt16Div10, 2, 1, "°C")          \
  X(VEBus_Reset, 62, 228, convertNone, 0, 1, "")                                 \
  X(VE_Bus_Phase_rotation_warning, 63, 228, convertNone, 0, 1, "")               \
  X(VE_Bus_Grid_lost_alarm, 64, 228, convertNone, 0, 1, "")                      \
  X(VE_Bus_Feed_DC_overvoltage_into_grid, 65, 228, convertNone, 0, 1, "")        \
  X(VE_Bus_Maximum_overvoltage_feed_in_power_L1, 66, 228, convertNone, 0, 1, "W")\
  X(VE_Bus_Maximum_overvoltage_feed_in_power_L2, 67, 228, convertNone, 0, 1, "W")\
  X(VE_Bus_Maximum_overvoltage_feed_in_power_L3, 68, 228, convertNone, 0, 1, "W")\
  X(VE_Bus_AC_input_1_ignored, 69, 228, convertNone, 0, 1, "")                   \
  X(VE_Bus_AC_input_2_ignored, 70, 228, convertNone, 0, 1, "")                   \
  X(VE_Bus_AcPowerSetpoint_acts_as_feed_in_limit, 71, 228, convertNone,0,1, "W") \
  X(VE_Bus_Solar_offset_voltage, 72, 228, convertNone, 0, 1, "V")                \
  X(VE_Bus_Sustain_active, 73, 228, convertNone, 0, 1, "")                       \
  X(VE_Bus_Low_cell_voltage_imminent, 94, 228, convertNone, 0, 1, "")            \
  X(VE_Bus_Charge_state, 95, 228, convertNone, 0, 1, "")                         \
  X(Battery_power, 258, 225, convertInt16, 0, 1, "W")                            \
  X(Battery_voltage, 259, 225, convertDiv100, 2, 1, "V")                         \
  X(Battery_Starter_battery_voltage, 260, 225, convertDiv100, 2, 1, "V")         \
  X(Battery_Current, 261, 225, convertInt16Div10, 2, 1, "A")                     \
  X(Battery_Temperature, 262, 225, convertInt16Div10, 2, 1, "°C")                \
  X(Battery_MidPointVoltageOfTheBatteryBank, 263, 225, convertDiv100, 2, 1, "V") \
  X(Battery_MidPointDeviationOfTheBatteryBank, 264, 225, convertDiv100,2, 1, "V")\
  X(Battery_Consumed_Amphours, 265, 225, convertSub10, 2, 1, "Ah")               \
  X(Battery_State_of_Charge, 266, 225, convertDiv10, 0, 1, "%")                  \
  X(Battery_Alarm, 267, 225, convertNone, 0, 1, "")                              \
  X(Battery_Low_voltage_alarm, 268, 225, convertNone, 0, 1, "")                  \
  X(Battery_High_voltage_alarm, 269, 225, convertNone, 0, 1, "")                 \
  X(Battery_Low_starter_voltage_alarm, 270, 225, convertNone, 0, 1, "")          \
  X(Battery_High_starter_voltage_alarm, 271, 225, convertNone, 0, 1, "")         \
  X(Battery_Low_State_of_charge_alarm, 272, 225, convertNone, 0, 1, "")          \
  X(Battery_Low_temperature_alarm, 273, 225, convertNone, 0, 1, "")              \
  X(Battery_High_temperature_alarm, 274, 225, convertNone, 0, 1, "")             \
  X(Battery_Mid_voltage_alarm, 275, 225, convertNone, 0, 1, "")                  \
  X(Battery_Low_fused_voltage_alarm, 276, 225, convertNone, 0, 1, "")            \
  X(Battery_High_fused_voltage_alarm, 277, 225, convertNone, 0, 1, "")           \
  X(Battery_Fuse_blown_alarm, 278, 225, convertNone, 0, 1, "")                   \
  X(Battery_High_internal_temperature_alarm, 279, 225, convertNone, 0, 1, "")    \
  X(Battery_Relay_status, 280, 225, convertNone, 0, 1, "")                       \
  X(Battery_Deepest_discharge, 281, 225, convertSub10, 1, 1, "Ah")               \
  X(Battery_Last_discharge, 282, 225, convertSub10, 1, 1, "Ah")                  \
  X(Battery_Average_discharge, 283, 225, convertSub10, 1, 1, "Ah")               \
  X(Battery_Charge_cycles, 284, 225, convertNone, 0, 1, "cnt")                   \
  X(Battery_Full_discharges, 285, 225, convertNone, 0, 1, "cnt")                 \
  X(Battery_Total_Ah_drawn, 286, 225, convertSub10, 1, 1, "Ah")                  \
  X(Battery_Minimum_voltage, 287, 225, convertDiv100, 3, 1, "V")                 \
  X(Battery_Maximum_voltage, 288, 225, convertDiv100, 3, 1, "V")                 \
  X(Battery_Time_since_last_full_charge, 289, 225, convertNone, 0, 1, "s")       \
  X(Battery_Automatic_syncs, 290, 225, convertNone, 0, 1, "cnt")                 \
  X(Battery_Low_voltage_alarms, 291, 225, convertNone, 0, 1, "cnt")              \
  X(Battery_High_voltage_alarms, 292, 225, convertNone, 0, 1, "cnt")             \
  X(Battery_State_of_Health, 304, 225, convertDiv10, 1, 1, "%")                  \
  X(Batter_Max_charge_voltage, 305, 225, convertDiv10, 1, 1, "V")                \
  X(Batter_Min_discharge_voltage, 306, 225, convertDiv10, 1, 1, "V")             \
  X(Batter_Max_charge_current, 307, 225, convertDiv10, 1, 1, "A")                \
  X(Batter_Max_discharge_current, 308, 225, convertDiv10, 1, 1, "A")             \
  X(Battery_Capacity, 309, 225, convertDiv10, 1, 1, "Ah")                        \
  X(Battery_Minimum_cell_temperature, 318, 225, convertInt16Div10, 1, 1, "°C")   \
  X(Battery_Maximum_cell_temperature, 319, 225, convertInt16Div10, 1, 1, "°C")   \
  X(Battery_High_charge_current_alarm, 320, 225, convertNone, 0, 1, "")          \
  X(Battery_High_discharge_current_alarm, 321, 225, convertNone, 0, 1, "")       \
  X(Battery_Cell_imbalance_alarm, 322, 225, convertNone, 0, 1, "")               \
  X(Battery_Internal_failure_alarm, 323, 225, convertNone, 0, 1, "")             \
  X(Battery_High_charge_temperature_alarm, 324, 225, convertNone, 0, 1, "")      \
  X(Battery_Low_charge_temperature_alarm, 325, 225, convertNone, 0, 1, "")       \
  X(Battery_Low_cell_voltage_alarm, 326, 225, convertNone, 0, 1, "")             \
  X(Battery_Mode, 327, 225, convertNone, 0, 1, "")                               \
  X(Battery_State, 1282, 225, convertNone, 0, 1, "")                             \
  X(Battery_Error, 1283, 225, convertNone, 0, 1, "")                             \
  X(Battery_System_switch, 1284, 225, convertNone, 0, 1, "")                     \
  X(Battery_Balancing, 1285, 225, convertNone, 0, 1, "")                         \
  X(Battery_number_of_batteries, 1286, 225, convertNone, 0, 1, "")               \
  X(Battery_batteries_parallel, 1287, 225, convertNone, 0, 1, "")                \
  X(Battery_batteries_series, 1288, 225, convertNone, 0, 1, "")                  \
  X(Battery_number_of_cells_per_battery, 1289, 225, convertNone, 0, 1, "")       \
  X(Battery_Min_cell_voltage, 1290, 225, convertDiv100, 2, 1, "V")               \
  X(Battery_Max_cell_voltage, 1291, 225, convertDiv100, 2, 1, "V")               \
  X(Battery_number_of_modules_offline, 1302, 225, convertNone, 0, 1, "")         \
  X(Battery_number_of_modules_online, 1303, 225, convertNone, 0, 1, "")          \
  X(Battery_number_of_modules_blocking_charge, 1304, 225, convertNone, 0, 1, "") \
  X(Battery_number_of_modules_blocking_discharge, 1305, 225, convertNone,0,1, "")\
  X(Battery_mode, 1319, 225, convertNone, 0, 1, "")                              \
  X(Battery_Balancer_status, 1320, 225, convertNone, 0, 1, "")                   \
  X(Grid_L1_Power, 2600, 40, convertInt16, 0, 1, "W")                            \
  X(Grid_L2_Power, 2601, 40, convertInt16, 0, 1, "W")                            \
  X(Grid_L3_Power, 2602, 40, convertInt16, 0, 1, "W")                            \
  X(Grid_L1_Energy_from_net, 2603, 40, convertInt16Div100, 2, 1, "kWh")          \
  X(Grid_L2_Energy_from_net, 2604, 40, convertInt16Div100, 2, 1, "kWh")          \
  X(Grid_L3_Energy_from_net, 2605, 40, convertInt16Div100, 2, 1, "kWh")          \
  X(Grid_L1_Energy_to_net, 2606, 40, convertInt16Div100, 2, 1, "kWh")            \
  X(Grid_L2_Energy_to_net, 2607, 40, convertInt16Div100, 2, 1, "kWh")            \
  X(Grid_L3_Energy_to_net, 2608, 40, convertInt16Div100, 2, 1, "kWh")            \
  X(Grid_L1_Voltage, 2616, 40, convertDiv10, 1, 1, "V")                          \
  X(Grid_L1_Current, 2617, 40, convertInt16Div10, 1, 1, "A")                     \
  X(Grid_L2_Voltage, 2618, 40, convertDiv10, 1, 1, "V")                          \
  X(Grid_L2_Current, 2619, 40, convertInt16Div10, 1, 1, "A")                     \
  X(Grid_L3_Voltage, 2620, 40, convertDiv10, 1, 1, "V")                          \
  X(Grid_L3_Current, 2621, 40, convertInt16Div10, 1, 1, "A")                     \
  X(Grid_AC_Frequency, 2644, 40, convertDiv100, 1, 1, "Hz")                      \
  X(Grid_Total_Energy_from_net, 2634, 40, convertInt32Div100, 2, 2, "kWh")       \
  X(Grid_Total_Energy_to_net, 2636, 40, convertInt32Div100, 2, 2, "kWh")





  
