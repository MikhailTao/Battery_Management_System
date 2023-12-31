/*
 * BMS_Button.h
 *
 *  Created on: 2023-12-29
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: Button for external interruption
 */

#ifndef BMS_BMS_BUTTON_H_
#define BMS_BMS_BUTTON_H_

interrupt void xint1_isr(void);
interrupt void xint2_isr(void);
interrupt void xint3_isr(void);
interrupt void xint4_isr(void);

float const Voltage_Step = 0.5;

#endif /* BMS_BMS_BUTTON_H_ */
