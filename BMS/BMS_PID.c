/*
 * BMS_PID.c
 *
 *  Created on: 2023-12-29
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This is source file of PID controller
 */

#include "F2837xD_device.h"        // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"      // F2837xD Examples Include File
#include "BMS_Ext.h"
#include "BMS_PID.h"
#include <math.h>

void PID_Update(struct Slot* s) {
    float D = 0;

    s->Error = s->Reff_Voltage - s->Volatge;
    s->Integral += s->Error * Ts;
    s->Derivative = (s->Error - s->PrevError)/Ts;

    D = (Kp * s->Error) + (Ki * s->Integral) + (Kd * s->Derivative);

    if (D > maxOutput) s->DutyRatio = maxOutput;
    else if (D < minOutput) s->DutyRatio = minOutput;
    else s->DutyRatio = D;
}


