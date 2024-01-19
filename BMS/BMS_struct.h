/*
 * BMS_struct.h
 *
 *  Created on: 2023-12-29
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This file contains all typedef of struct / union
 */

#ifndef BMS_BMS_STRUCT_H_
#define BMS_BMS_STRUCT_H_

#include "BMS_enum.h"

struct  Slot    {
                enum    BATTERY_STATE   BatteryState;
                float   Volatge;
                float   DutyRatio;
                float   Diff_Voltage;
                float   Reff_Voltage;

                float   Error;
                float   PrevError;
                float   Derivative;
                float   Integral;
                };

union CharFloat {
                unsigned char str[2];
                float Value;
                };

#endif /* BMS_BMS_STRUCT_H_ */
