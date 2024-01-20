/*
 * BMS_LCD12864.h
 *
 *  Created on: 2024-01-19
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: LCD header file
 */

#ifndef BMS_BMS_LCD12864_H_
#define BMS_BMS_LCD12864_H_

void LCD_GPIO(void);
void LCD_DATA(unsigned char d);
void Init_LCD(void);
void Write_order(Uint16 order);
void Write_data(Uint16 data);
void delay(Uint16 t);
void configio(void);
void display(unsigned char *hz);
void display_state (void);
void Init_Emif1(void);

Uint16  ErrCount = 0;

#define   LCD_DATA_BUS  (*((volatile  Uint16 *)0x380000))
#define   EN    GpioDataRegs.GPBDAT.bit.GPIO56
#define   RW    GpioDataRegs.GPBDAT.bit.GPIO57
#define   RS    GpioDataRegs.GPBDAT.bit.GPIO53

#endif /* BMS_BMS_LCD12864_H_ */
