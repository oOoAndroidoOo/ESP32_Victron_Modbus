#pragma once


#define REGISTER_LIST                                  \
X(REG_PV1, 52145321, 100, convertNone, 0)                   \
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
X(REG_Battery_Temp, 262, 225, convertDiv10, 2)         \
X(REG_Bat_MinCell_Voltage, 1290, 225, convertDiv100, 2) \
X(REG_Bat_MaxCell_Voltage, 1291, 225, convertDiv100, 2)
