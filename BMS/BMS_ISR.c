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
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag

    //
    // Check if overflow has occurred
    //
    if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

    Read_Adc_Data ();  //读取ADC转化的结果

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;  //P0 对应第1组

    // Calibration
    ADC_Cali ();
}

void ADC_Cali (void){
    if (1 == flag_cali)
    {
        ADC_Convert_Offset_0 = ADC_0;
        ADC_Convert_Offset_1 = ADC_1;
        ADC_Convert_Offset_2 = ADC_2;
        ADC_Convert_Offset_3 = ADC_3;
        flag_cali = 0;
    }
}

void Duty_Update (void){
    EPwm1Regs.CMPA.bit.CMPA = 0;
}
