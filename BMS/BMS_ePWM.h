/*
 * BMS_EPWM.h
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This file stores ePWM settings
 */

#ifndef BMS_BMS_EPWM_H_
#define BMS_BMS_EPWM_H_

void PWM_Init(void);
void EPWM1_Init(void);
void EPWM2_Init(void);

int tbprd   =   5000;            // ePWM period length 200e6Hz/1e5Hz

#endif /* BMS_BMS_EPWM_H_ */
