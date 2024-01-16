/*
 * BMS_ISR.c
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This is interrupt service routine
 */

#include "F2837xD_device.h"        // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"      // F2837xD Examples Include File
#include <math.h>
#include <float.h>
#include "BMS_Ext.h"
#include "BMS_ISR.h"
#include "BMS_struct.h"


extern void Read_Adc_Data (void);

interrupt void ISR(void)
{
    EPwm1Regs.ETCLR.bit.INT = 1;                                                    // Clear Interrupt Flag ETFLG.INT = 0

    Read_Adc_Data ();                                                               // Read ADC result                                                                  // Calibration

//    Assign_Reading();
//    Voltage_Change_Rate();

    Feedback_Package_Prepare();

//    System_Control();

    if(PieCtrlRegs.PIEIFR3.bit.INTx1 == 1) flag_overflow = 1;                       // Overflow?
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//void Duty_Update (void){
//    PID_Update(&Slot_1);
//    PID_Update(&Slot_2);
//    PID_Update(&Slot_3);
//    EPwm1Regs.CMPA.bit.CMPA = floor(Slot_1.DutyRatio * tbprd);
//    EPwm2Regs.CMPA.bit.CMPA = floor(Slot_2.DutyRatio * tbprd);
//    EPwm3Regs.CMPA.bit.CMPA = floor(Slot_3.DutyRatio * tbprd);
//}
//
//void Assign_Reading (void){
//    Slot_1.Volatge = ADC_A0;
//    Slot_2.Volatge = ADC_A1;
//    Slot_3.Volatge = ADC_A2;
//}
//
//void System_Control (void){
//    if(SysState == ON){
//        Duty_Update();
//    }
//    else{
//        EPwm1Regs.CMPA.bit.CMPA = 0;
//        EPwm2Regs.CMPA.bit.CMPA = 0;
//        EPwm3Regs.CMPA.bit.CMPA = 0;
//    }
//}
//
//void Voltage_Change_Rate (void){
//    Slot_1.Diff_Voltage = (ADC_A0 - Slot_1.Volatge);
//    Slot_2.Diff_Voltage = (ADC_A1 - Slot_2.Volatge);
//    Slot_3.Diff_Voltage = (ADC_A2 - Slot_3.Volatge);
//}

//void Slot_Init (void){
//    Slot_Init_single(&Slot_1);
//    Slot_Init_single(&Slot_2);
//    Slot_Init_single(&Slot_3);
//}

// Collect Data
void Feedback_Package_Prepare(void){
    if (Feedback_Package_Index >= Data_Package_Size){
        if (Data_Package_Transmission == Wait_For_Data){
            if (Data_Package_Select == DC3_save_DC4_transmit){
                Data_Center_3_Ready = Ready;
                Data_Package_Select = DC3_transmit_DC4_save;
            } else {
                Data_Center_4_Ready = Ready;
                Data_Package_Select = DC3_save_DC4_transmit;
            }
        } else{
            if (Data_Center_3_Ready == Ready){
                Data_Center_3_Ready = NotReady;
            }
            if (Data_Center_4_Ready == Ready){
                Data_Center_4_Ready = NotReady;
            }
        }
        Feedback_Package_Index = 0;     // Reset Counter
    }

    if (Data_Sample_Cycle_Count == Data_Sample_Cycle){
        Data_Sample_Cycle_Count = 0;
    }

    if (Data_Package_Select == DC3_save_DC4_transmit && Data_Sample_Cycle_Count == Data_Sample_Cycle-1){
        Data_Center_3[Feedback_Package_Index + Data_Package_Size*0] = ADC_A0;
        Data_Center_3[Feedback_Package_Index + Data_Package_Size*1] = ADC_A1;
        Data_Center_3[Feedback_Package_Index + Data_Package_Size*2] = ADC_A2;
        Feedback_Package_Index++;
    } else if (Data_Package_Select == DC3_transmit_DC4_save && Data_Sample_Cycle_Count == Data_Sample_Cycle-1){
        Data_Center_4[Feedback_Package_Index + Data_Package_Size*0] = ADC_A0;
        Data_Center_4[Feedback_Package_Index + Data_Package_Size*1] = ADC_A1;
        Data_Center_4[Feedback_Package_Index + Data_Package_Size*2] = ADC_A2;
        Feedback_Package_Index++;
    }

    Data_Sample_Cycle_Count++;
}

//void Slot_Init_single(struct Slot* s){
//    s->BatteryState = None;
//    s->Diff_Voltage = 0.0f;
//    s->DutyRatio = 0.0f;
//    s->Volatge = 0.0f;
//    s->Reff_Voltage = 15.0f;                // 15V
//    s->Error = 0.0f;
//    s->PrevError = 0.0f;
//    s->Derivative = 0.0f;
//    s->Integral = 0.0f;
//}
