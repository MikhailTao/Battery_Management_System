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

void ISR(void);
void ADC_Cali (void);
void Duty_Update (void);
void Assign_Reading (void);
void System_Control (void);
void Voltage_Change_Rate (void);
void Slot_Init (void);
void Feedback_Package_Prepare(void);
void Slot_Init_single(struct Slot* s);
void LED (void);

extern void PID_Update(struct Slot* s);

unsigned    int     flag_cali = 0;
unsigned    int     flag_overflow = 0;

extern      float   ADC_A0, ADC_A1, ADC_A2;

// For LED
#define LED1_ON  GpioDataRegs.GPASET.bit.GPIO0 = 1
#define LED1_OFF GpioDataRegs.GPACLEAR.bit.GPIO0 = 1
#define LED2_ON  GpioDataRegs.GPASET.bit.GPIO1 = 1
#define LED2_OFF GpioDataRegs.GPACLEAR.bit.GPIO1 = 1
#define LED3_ON  GpioDataRegs.GPASET.bit.GPIO2 = 1
#define LED3_OFF GpioDataRegs.GPACLEAR.bit.GPIO2 = 1
#define LED4_ON  GpioDataRegs.GPASET.bit.GPIO3 = 1
#define LED4_OFF GpioDataRegs.GPACLEAR.bit.GPIO3 = 1
#define LED5_ON  GpioDataRegs.GPASET.bit.GPIO4 = 1
#define LED5_OFF GpioDataRegs.GPACLEAR.bit.GPIO4 = 1
#define LED6_ON  GpioDataRegs.GPASET.bit.GPIO5 = 1
#define LED6_OFF GpioDataRegs.GPACLEAR.bit.GPIO5 = 1

#endif /* BMS_BMS_ISR_H_ */
