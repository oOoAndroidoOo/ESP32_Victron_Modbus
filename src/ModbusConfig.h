#pragma once

// Eigene Definition der REGISTER_LIST
#define REGISTER_LIST                                             \
  X(PV_AC_coupled_on_output_L1, 808, 100, convertNone, 0)         \
  X(PV_AC_coupled_on_input_L1, 811, 100, convertNone, 0)          \
  X(AC_Consumption_L1, 817, 100, convertNone, 0)                  \
  X(AC_Consumption_L2, 818, 100, convertNone, 0)                  \
  X(AC_Consumption_L3, 819, 100, convertNone, 0)                  \
  X(Active_input_source, 826, 100, convertInt16, 0)               \
  X(Battery_Voltage_System, 840, 100, convertDiv10, 2)            \
  X(Battery_Current_System, 841, 100, convertInt16Div10, 2)       \
  X(Battery_Power_System, 842, 100, convertInt16, 2)              \
  X(Battery_State_of_Charge_System, 843, 100, convertNone, 0)     \
  X(Battery_State_System, 844, 100, convertNone, 0)               \
  X(VEBus_charge_current_System, 865, 100, convertInt16Div10, 2)  \
  X(VEBus_charge_Power_System, 866, 100, convertInt16, 2)         \
  X(PowerOnOutputOfInverterCharger_L1, 878, 100, convertInt32, 2) \
  X(Inverter_Charger_Power, 870, 100, convertInt32, 2)            \
  X(Input_voltage_phase_1, 3, 228, convertDiv10, 2)               \
  X(Input_current_phase_1, 6, 228, convertInt16Div10, 2)          \
  X(Input_frequency_phase_1, 9, 228, convertInt16Div100, 2)       \
  X(Input_power_phase_1, 12, 228, convertInt16, 2)                \
  X(Output_voltage_phase_1, 15, 228, convertDiv10, 2)             \
  X(Output_current_phase_1, 18, 228, convertInt16Div10, 2)        \
  X(Output_frequency_phase_1, 21, 228, convertInt16Div100, 2)     \
  X(Active_input_current_limit, 22, 228, convertInt16Div10, 0)    \
  X(Output_power_1, 23, 228, convertInt16Mul10, 2)                \
  X(Battery_voltage, 26, 228, convertDiv100, 2)                   \
  X(Battery_current, 27, 228, convertInt16Div10, 2)               \
  X(Phase_count, 28, 228, convertNone, 0)                         \
  X(Active_input, 29, 228, convertNone, 0)                        \
  X(VE_Bus_StateOfCharge, 30, 228, convertDiv10, 0)               \
  X(VE_Bus_State, 31, 228, convertNone, 0)                        \
  X(VE_Bus_Error, 32, 228, convertNone, 0)                        \
  X(Switch_position, 33, 228, convertNone, 0)                     \
  X(Temperature_alarm, 34, 228, convertNone, 0)                   \
  X(Low_Battery_alarm, 35, 228, convertNone, 0)                   \
  X(Overload_alarm, 36, 228, convertNone, 0)                      \
  X(ESS_power_setpoint_phase1, 37, 228, convertInt16, 0)          \
  X(ESS_disable_charge_flag_phase, 38, 228, convertNone, 0)       \
  X(ESS_disable_feedback_flag_phase, 39, 228, convertNone, 0)     \
  X(ESS_power_setpoint_phase2, 40, 228, convertInt16, 0)          \
  X(ESS_power_setpoint_phase3, 41, 228, convertInt16, 0)
