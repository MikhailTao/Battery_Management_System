/*
 * BMS_SEG7.h
 *
 *  Created on: 2023��12��30��
 *      Author: Tao Ran
 */

#ifndef BMS_BMS_SEG7_H_
#define BMS_BMS_SEG7_H_

void SEG7_Display(void);
void SEG7_GPIO(void);
void SEG_DATA(unsigned char d);

int Digit1 = 0, Digit2 = 0, Digit3 = 0;

#endif /* BMS_BMS_SEG7_H_ */
