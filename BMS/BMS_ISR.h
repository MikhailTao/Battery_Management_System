/*
 * BMS_ISR.h
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This is interrupt service routine for ADC
 */

#ifndef BMS_BMS_ISR_H_
#define BMS_BMS_ISR_H_

void ISR(void);
void ADC_Cali (void);

unsigned int sample_counter = 100;
unsigned int flag_cali = 0;

#endif /* BMS_BMS_ISR_H_ */
