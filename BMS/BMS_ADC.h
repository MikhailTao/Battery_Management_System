/*
 * BMS_ADC.h
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This file stores all information about ADC module
 */


#ifndef BMS_BMS_ADC_H_
#define BMS_BMS_ADC_H_

void SetupADC(void);
void Init_ADC(void);
void Read_Adc_Data (void);

Uint16      acqps = 149;                                // 75ns-14

float       ADC_A0,
            ADC_A1,
            ADC_A2,
            ADC_A3,
            ADC_A4,
            ADC_A5,
            ADC_A14,
            ADC_A15,
            ADC_B0,
            ADC_B1,
            ADC_B2,
            ADC_B3,
            ADC_C2,
            ADC_C3,
            ADC_C4,
            ADC_D0,
            ADC_D1,
            ADC_D2,
            ADC_D3,
            ADC_D4;

float       ADC_Convert_Constant        =   3.3/4095;

float       ADC_Convert_Constant_A0     =   1,
            ADC_Convert_Constant_A1     =   1,
            ADC_Convert_Constant_A2     =   1,
            ADC_Convert_Constant_A3     =   1,
            ADC_Convert_Constant_A4     =   1,
            ADC_Convert_Constant_A5     =   1,
            ADC_Convert_Constant_A14    =   1,
            ADC_Convert_Constant_A15    =   1,
            ADC_Convert_Constant_B0     =   1,
            ADC_Convert_Constant_B1     =   1,
            ADC_Convert_Constant_B2     =   1,
            ADC_Convert_Constant_B3     =   1,
            ADC_Convert_Constant_C2     =   1,
            ADC_Convert_Constant_C3     =   1,
            ADC_Convert_Constant_C4     =   1,
            ADC_Convert_Constant_D0     =   1,
            ADC_Convert_Constant_D1     =   1,
            ADC_Convert_Constant_D2     =   1,
            ADC_Convert_Constant_D3     =   1,
            ADC_Convert_Constant_D4     =   1;

float       ADC_Convert_Offset_A0   =   0,
            ADC_Convert_Offset_A1   =   0,
            ADC_Convert_Offset_A2   =   0,
            ADC_Convert_Offset_A3   =   0,
            ADC_Convert_Offset_A4   =   0,
            ADC_Convert_Offset_A5   =   0,
            ADC_Convert_Offset_A14  =   0,
            ADC_Convert_Offset_A15  =   0,
            ADC_Convert_Offset_B0   =   0,
            ADC_Convert_Offset_B1   =   0,
            ADC_Convert_Offset_B2   =   0,
            ADC_Convert_Offset_B3   =   0,
            ADC_Convert_Offset_C2   =   0,
            ADC_Convert_Offset_C3   =   0,
            ADC_Convert_Offset_C4   =   0,
            ADC_Convert_Offset_D0   =   0,
            ADC_Convert_Offset_D1   =   0,
            ADC_Convert_Offset_D2   =   0,
            ADC_Convert_Offset_D3   =   0,
            ADC_Convert_Offset_D4   =   0;

#endif /* BMS_BMS_ADC_H_ */
