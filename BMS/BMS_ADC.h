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
void InitADC(void);
void Read_Adc_Data (void);

Uint16      acqps = 149;                                // 75ns-14
float       ADC_0, ADC_1, ADC_2, ADC_3, ADC_4;

float       ADC_Convert_Constant    =   3/4095;
float       ADC_Convert_Constant_0  =   1,
            ADC_Convert_Constant_1  =   1,
            ADC_Convert_Constant_2  =   1,
            ADC_Convert_Constant_3  =   1;
float       ADC_Convert_Offset_0    =   0,
            ADC_Convert_Offset_1    =   0,
            ADC_Convert_Offset_2    =   0,
            ADC_Convert_Offset_3    =   0;

#endif /* BMS_BMS_ADC_H_ */
