/*
 * BMS_SEG7.c
 *
 *  Created on: 2023Äê12ÔÂ30ÈÕ
 *      Author: Tao Ran
 */

#include "F2837xD_device.h"                         // F2837xD Header file Include File
#include "F2837xD_Examples.h"                       // F2837xD Examples Include File
#include "BMS_SEG7.h"
#include "BMS_Ext.h"
#include <math.h>

void SEG7_Display(void){
    if (Slot_Select == Slot1){
        Digit1 = floor(Slot_1.Reff_Voltage/10);
        Digit2 = floor(Slot_1.Reff_Voltage - 10*Digit1);
        Digit3 = (Slot_1.Reff_Voltage - 10*Digit1 - Digit2)==0 ? 0:5;
    }
    else if (Slot_Select == Slot2){
        Digit1 = floor(Slot_2.Reff_Voltage/10);
        Digit2 = floor(Slot_2.Reff_Voltage - 10*Digit1);
        Digit3 = (Slot_2.Reff_Voltage - 10*Digit1 - Digit2)==0 ? 0:5;
    }
    else{
        Digit1 = floor(Slot_3.Reff_Voltage/10);
        Digit2 = floor(Slot_3.Reff_Voltage - 10*Digit1);
        Digit3 = (Slot_3.Reff_Voltage - 10*Digit1 - Digit2)==0 ? 0:5;
    }

    SEG_DATA(seg7_table[0]);
    SBIT0=0;DELAY_US(1);
    SBIT2=1;DELAY_US(1);
    SBIT1=1;DELAY_US(1);
    SBIT3=1;
    DELAY_US(100);
    SBIT0=1;
    SEG_DATA(0);

    SEG_DATA(seg7_table[Digit1]);
    SBIT1=0;DELAY_US(1);
    SBIT2=1;DELAY_US(1);
    SBIT3=1;DELAY_US(1);
    SBIT0=1;
    DELAY_US(100);
    SBIT1=1;
    SEG_DATA(0);

    SEG_DATA(seg7_table[Digit2]|0x01);
    SBIT2=0;DELAY_US(1);
    SBIT1=1; DELAY_US(1);
    SBIT3=1;DELAY_US(1);
    SBIT0=1;
    DELAY_US(100);
    SBIT2=1;
    SEG_DATA(0);

    SEG_DATA(seg7_table[Digit3]);
    SBIT3=0;DELAY_US(1);
    SBIT1=1;DELAY_US(1);
    SBIT2=1;DELAY_US(1);
    SBIT0=1;
    DELAY_US(100);
    SBIT3=1;
    SEG_DATA(0);
}

void SEG7_GPIO(void){
    GPIO_SetupPinMux(58, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(58, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(59, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(59, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(60, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(60, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(61, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(61, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(77, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(77, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(78, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(78, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(79, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(79, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(80, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(80, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(81, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(81, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(82, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(82, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(83, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(83, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(85, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(85, GPIO_OUTPUT, GPIO_PUSHPULL);
}

void SEG_DATA(unsigned char d)
{
    Uint32 dat1 = 0,dat2 = 0;
    dat1 = d;
    dat1 <<= 13;
    dat2 = d;
    dat2 <<= 13;
    dat2 &= 0x100000;
    dat2 <<= 1;
    dat1 |= dat2;
    GpioDataRegs.GPCDAT.all = dat1;
}
