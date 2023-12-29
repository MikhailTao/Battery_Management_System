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

Uint16 InterruptCount1 = 0,InterruptCount2 = 0,InterruptCount3 = 0,InterruptCount4 = 0;

#endif /* BMS_BMS_BUTTON_H_ */
