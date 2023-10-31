/*
 * BMS_ADC.c
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This file stores ADC information about the ADC module
 */

#include "F2837xD_device.h"        // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"      // F2837xD Examples Include File
#include "BMS_ADC.h"

void SetupADC(void)  //设置ADC的触发信息，SOC
{
    //determine minimum acquisition window (in SYSCLKS) based on resolution
    //   设置采样保持时间
    if (ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
    {
        acqps = 149; //75ns-14
    }
    else
    { //resolution is 16-bit
        acqps = 63; //320ns
    }

    acqps = 99; //sample window is 100 SYSCLK cycles
    //Select the channels to convert and end of conversion flag
    //ADCA
    EALLOW;
    AdcaRegs.ADCSOCFRC1.all = 0x000F;
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 19; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0X5; //trigger on epwm1 SOCA

    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 3;  //SOC1 will convert pin A3
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0; //trigger on software SOCA

    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 4;  //SOC0 will convert pin A4
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 0; //trigger on software SOCA

    AdcaRegs.ADCSOC3CTL.bit.CHSEL = 5;  //SOC0 will convert pin A5
    AdcaRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 0; //trigger on ePWM2 SOCA

    //AdcaRegs.ADCINTSEL1N2.bit.INT2CONT = 1; //enable continuous mode
    EDIS;

}

void InitADC(void)
{
    EALLOW;

    //write configurations
    // 分频
    AdcaRegs.ADCCTL2.bit.PRESCALE = 14; //set ADCCLK divider to /4
    AdcbRegs.ADCCTL2.bit.PRESCALE = 14; //set ADCCLK divider to /4
    AdccRegs.ADCCTL2.bit.PRESCALE = 14; //set ADCCLK divider to /4
    AdcdRegs.ADCCTL2.bit.PRESCALE = 14; //set ADCCLK divider to /4
    //  设置A,B,C,D四个寄存器的ADC模式，12位精度，单端模式
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //Set pulse positions to late
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //power up the ADC 给ADC上电
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //delay for 1ms to allow ADC time to power up
    DELAY_US(1000);
    EDIS;

    //设置ADC的触发信息，SOC
    SetupADC();

    //打开ADC中断
    EALLOW;
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; //end of SOC0 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E   = 1;   //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
    EDIS;

    EALLOW;
    CpuSysRegs.PCLKCR13.bit.ADC_A = 1; //open ADC_A clock
    CpuSysRegs.PCLKCR13.bit.ADC_B = 1; //open ADC_B clock
    CpuSysRegs.PCLKCR13.bit.ADC_C = 1; //open ADC_C clock
    CpuSysRegs.PCLKCR13.bit.ADC_D = 1; //open ADC_D clock

    EDIS;
}

void Read_Adc_Data (void)  //读取ADC的转换值
{
    ADC_0 = (float)AdcaResultRegs.ADCRESULT0 * ADC_Convert_Constant_0 - ADC_Convert_Offset_0; //读取ADC的结果，对应pin A0
    ADC_1 = (float)AdcaResultRegs.ADCRESULT1 * ADC_Convert_Constant_1 - ADC_Convert_Offset_1; //读取ADC的结果，对应pin A3
    ADC_2 = (float)AdcaResultRegs.ADCRESULT2 * ADC_Convert_Constant_2 - ADC_Convert_Offset_2; //读取ADC的结果，对应pin A4
    ADC_3 = (float)AdcaResultRegs.ADCRESULT3 * ADC_Convert_Constant_3 - ADC_Convert_Offset_3; //读取ADC的结果，对应pin A5
}
