/*
 * BMS_PID.h
 *
 *  Created on: 2023-12-29
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This is header file of PID controller
 */

#ifndef BMS_BMS_PID_H_
#define BMS_BMS_PID_H_

#include "BMS_struct.h"

float   maxOutput = 1.0f;                                                   // Maximum output limit
float   minOutput = 0.0f;                                                   // Minimum output limit

void PID_Update(struct Slot* s);

#endif /* BMS_BMS_PID_H_ */
