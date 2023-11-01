/*
 * BMS_ISR.c
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This is interrupt service routine for ADC
 */

#include "F2837xD_device.h"        // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"      // F2837xD Examples Include File
#include "BMS_Ext.h"
#include "BMS_ISR.h"

extern void Read_Adc_Data (void);

interrupt void ISR(void)  //中断读取ADC转换的数据
{
    EPwm1Regs.ETCLR.bit.INT = 1;  // Clear Interrupt Flag ETFLG.INT = 0

    Read_Adc_Data ();  //读取ADC转化的结果

    // Calibration
    ADC_Cali ();

    if(PieCtrlRegs.PIEIFR3.bit.INTx1 == 1)//overflow or not
    {
        flag_overflow = 1;
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

void ADC_Cali (void){
    if (1 == flag_cali)
    {
        flag_cali = 0;
    }
}

void Duty_Update (void){
    //EPwm1Regs.CMPA.bit.CMPA = 0;
}
