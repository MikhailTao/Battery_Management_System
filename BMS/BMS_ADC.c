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

    EALLOW;
    // ADC A
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;          //SOC0 will convert pin A0
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 1;          //SOC1 will convert pin A1
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 2;          //SOC2 will convert pin A2
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcaRegs.ADCSOC3CTL.bit.CHSEL = 3;          //SOC3 will convert pin A3
    AdcaRegs.ADCSOC3CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcaRegs.ADCSOC4CTL.bit.CHSEL = 4;          //SOC4 will convert pin A3
    AdcaRegs.ADCSOC4CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcaRegs.ADCSOC5CTL.bit.CHSEL = 5;          //SOC5 will convert pin A3
    AdcaRegs.ADCSOC5CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcaRegs.ADCSOC14CTL.bit.CHSEL = 14;        //SOC4 will convert pin A3
    AdcaRegs.ADCSOC4CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcaRegs.ADCSOC15CTL.bit.CHSEL = 15;        //SOC5 will convert pin A3
    AdcaRegs.ADCSOC5CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    // ADC B
    AdcbRegs.ADCSOC0CTL.bit.CHSEL = 0;          //SOC6 will convert pin B0
    AdcbRegs.ADCSOC0CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcbRegs.ADCSOC1CTL.bit.CHSEL = 1;          //SOC1 will convert pin B1
    AdcbRegs.ADCSOC1CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC1CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcbRegs.ADCSOC2CTL.bit.CHSEL = 2;          //SOC0 will convert pin B2
    AdcbRegs.ADCSOC2CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcbRegs.ADCSOC3CTL.bit.CHSEL = 3;          //SOC0 will convert pin B3
    AdcbRegs.ADCSOC3CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC3CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    // ADC C
    AdccRegs.ADCSOC0CTL.bit.CHSEL = 2;          //SOC0 will convert pin C2
    AdccRegs.ADCSOC0CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdccRegs.ADCSOC1CTL.bit.CHSEL = 3;          //SOC1 will convert pin C3
    AdccRegs.ADCSOC1CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdccRegs.ADCSOC2CTL.bit.CHSEL = 4;          //SOC0 will convert pin C4
    AdccRegs.ADCSOC2CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC2CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    // ADC D
    AdcdRegs.ADCSOC0CTL.bit.CHSEL = 0;          //SOC0 will convert pin D0
    AdcdRegs.ADCSOC0CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC0CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcdRegs.ADCSOC1CTL.bit.CHSEL = 1;          //SOC0 will convert pin D1
    AdcdRegs.ADCSOC1CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC1CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcdRegs.ADCSOC2CTL.bit.CHSEL = 2;          //SOC0 will convert pin D2
    AdcdRegs.ADCSOC2CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC2CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcdRegs.ADCSOC3CTL.bit.CHSEL = 3;          //SOC0 will convert pin D2
    AdcdRegs.ADCSOC3CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC3CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

    AdcdRegs.ADCSOC4CTL.bit.CHSEL = 4;          //SOC0 will convert pin D2
    AdcdRegs.ADCSOC4CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC4CTL.bit.TRIGSEL = 0X5;      //trigger on epwm1 SOCA

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
    AdcaRegs.ADCINTSEL1N2.bit.INT1E   = 1; //enable INT1 flag
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
    // ADC a
    ADC_A0  = (float)AdcaResultRegs.ADCRESULT0  * ADC_Convert_Constant_A0   * ADC_Convert_Constant  - ADC_Convert_Offset_A0;    //读取ADC的结果，对应pin A0
    ADC_A1  = (float)AdcaResultRegs.ADCRESULT1  * ADC_Convert_Constant_A1   * ADC_Convert_Constant  - ADC_Convert_Offset_A1;    //读取ADC的结果，对应pin A1
    ADC_A2  = (float)AdcaResultRegs.ADCRESULT2  * ADC_Convert_Constant_A2   * ADC_Convert_Constant  - ADC_Convert_Offset_A2;    //读取ADC的结果，对应pin A2
    ADC_A3  = (float)AdcaResultRegs.ADCRESULT3  * ADC_Convert_Constant_A3   * ADC_Convert_Constant  - ADC_Convert_Offset_A3;    //读取ADC的结果，对应pin A3
    ADC_A4  = (float)AdcaResultRegs.ADCRESULT4  * ADC_Convert_Constant_A4   * ADC_Convert_Constant  - ADC_Convert_Offset_A4;    //读取ADC的结果，对应pin A4
    ADC_A5  = (float)AdcaResultRegs.ADCRESULT5  * ADC_Convert_Constant_A5   * ADC_Convert_Constant  - ADC_Convert_Offset_A5;    //读取ADC的结果，对应pin A5
    ADC_A14 = (float)AdcaResultRegs.ADCRESULT14 * ADC_Convert_Constant_A14  * ADC_Convert_Constant  - ADC_Convert_Offset_A14;   //读取ADC的结果，对应pin A14
    ADC_A15 = (float)AdcaResultRegs.ADCRESULT15 * ADC_Convert_Constant_A15  * ADC_Convert_Constant  - ADC_Convert_Offset_A15;   //读取ADC的结果，对应pin A15

    // ADC b
    ADC_B0  = (float)AdcbResultRegs.ADCRESULT0  * ADC_Convert_Constant_B0   * ADC_Convert_Constant  - ADC_Convert_Offset_B0;    //读取ADC的结果，对应pin B0
    ADC_B1  = (float)AdcbResultRegs.ADCRESULT1  * ADC_Convert_Constant_B1   * ADC_Convert_Constant  - ADC_Convert_Offset_B1;    //读取ADC的结果，对应pin B1
    ADC_B2  = (float)AdcbResultRegs.ADCRESULT2  * ADC_Convert_Constant_B2   * ADC_Convert_Constant  - ADC_Convert_Offset_B2;    //读取ADC的结果，对应pin B2
    ADC_B3  = (float)AdcbResultRegs.ADCRESULT3  * ADC_Convert_Constant_B3   * ADC_Convert_Constant  - ADC_Convert_Offset_B3;    //读取ADC的结果，对应pin B3

    // ADC c
    ADC_C2  = (float)AdccResultRegs.ADCRESULT2  * ADC_Convert_Constant_C2   * ADC_Convert_Constant  - ADC_Convert_Offset_C2;    //读取ADC的结果，对应pin C2
    ADC_C3  = (float)AdccResultRegs.ADCRESULT3  * ADC_Convert_Constant_C3   * ADC_Convert_Constant  - ADC_Convert_Offset_C3;    //读取ADC的结果，对应pin C3
    ADC_C4  = (float)AdccResultRegs.ADCRESULT4  * ADC_Convert_Constant_C4   * ADC_Convert_Constant  - ADC_Convert_Offset_C4;    //读取ADC的结果，对应pin C4

    // ADC d
    ADC_D0  = (float)AdcdResultRegs.ADCRESULT0  * ADC_Convert_Constant_D0   * ADC_Convert_Constant  - ADC_Convert_Offset_D0;    //读取ADC的结果，对应pin D0
    ADC_D1  = (float)AdcdResultRegs.ADCRESULT1  * ADC_Convert_Constant_D1   * ADC_Convert_Constant  - ADC_Convert_Offset_D1;    //读取ADC的结果，对应pin D1
    ADC_D2  = (float)AdcdResultRegs.ADCRESULT2  * ADC_Convert_Constant_D2   * ADC_Convert_Constant  - ADC_Convert_Offset_D2;    //读取ADC的结果，对应pin D2
    ADC_D3  = (float)AdcdResultRegs.ADCRESULT3  * ADC_Convert_Constant_D3   * ADC_Convert_Constant  - ADC_Convert_Offset_D3;    //读取ADC的结果，对应pin D3
    ADC_D4  = (float)AdcdResultRegs.ADCRESULT4  * ADC_Convert_Constant_D4   * ADC_Convert_Constant  - ADC_Convert_Offset_D4;    //读取ADC的结果，对应pin D4
}
