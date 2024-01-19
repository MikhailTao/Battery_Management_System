/*
 * BMS_ISR.h
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This is header file of interrupt service routine
 */

#ifndef BMS_BMS_ISR_H_
#define BMS_BMS_ISR_H_

interrupt void ISR(void);

void ADC_Cali (void);
void Duty_Update (void);
void Assign_Reading (void);
void System_Control (void);
void Voltage_Change_Rate (void);

void Feedback_Package_Prepare(void);

extern void PID_Update(struct Slot* s);

unsigned    int     flag_cali = 0;
unsigned    int     flag_overflow = 0;

extern      float   ADC_A0, ADC_A1, ADC_A2;

#endif /* BMS_BMS_ISR_H_ */
