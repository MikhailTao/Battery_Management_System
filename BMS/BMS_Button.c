/*
 * BMS_Button.c
 *
 *  Created on: 2023-12-29
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: Button for external interruption
 */

#include "F2837xD_device.h"                         // F2837xD Header file Include File
#include "F2837xD_Examples.h"                       // F2837xD Examples Include File
#include "BMS_Ext.h"
#include "BMS_Button.h"

interrupt void xint1_isr(void)
{
    unsigned int press_count = 0;
    Button_Press = Short_Press;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    DELAY_US(1000);
    while(GpioDataRegs.GPADAT.bit.GPIO13 == 0){
        DELAY_US(10000);
        press_count++;
        if (press_count >= 100) Button_Press = Long_Press;
    }
    if (Button_Press == Long_Press){
        if (SysState == ON) SysState = OFF;
        else SysState = ON;
        Button_Press = Short_Press;
    }
    else{
        if (ChargeMode == Fast) ChargeMode = Balance;
        else ChargeMode = Fast;
    }
}

interrupt void xint2_isr(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    DELAY_US(10000);
    if(GpioDataRegs.GPADAT.bit.GPIO12 == 0){
        if (Slot_Select == Slot1) Slot_Select = Slot2;
        else if (Slot_Select == Slot2) Slot_Select = Slot3;
        else Slot_Select = Slot1;
    }
}

void Init_Exint(void){
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;            // GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;             // input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 1;           // XINT2 Synch to SYSCLKOUT only
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;            // GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;             // input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 1;           // XINT1 Synch to SYSCLKOUT only
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;            // GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;             // input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 1;           // XINT4 Synch to SYSCLKOUT only
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;            // GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;             // input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 1;           // XINT3 Synch to SYSCLKOUT only

    EDIS;
    GPIO_SetupXINT1Gpio(13);                        // GPIO12 is XINT1
    XintRegs.XINT1CR.bit.POLARITY = 0;              // Falling edge interrupt
    XintRegs.XINT1CR.bit.ENABLE = 1;                // Enable XINT2
    GPIO_SetupXINT2Gpio(12);                        // GPIO13 is XINT2
    XintRegs.XINT2CR.bit.POLARITY = 0;              // Falling edge interrupt
    XintRegs.XINT2CR.bit.ENABLE = 1;                // Enable XINT1
    GPIO_SetupXINT3Gpio(15);                        // GPIO14 is XINT3
    XintRegs.XINT3CR.bit.POLARITY = 0;              // Falling edge interrupt
    XintRegs.XINT3CR.bit.ENABLE = 1;                // Enable XINT1
    GPIO_SetupXINT4Gpio(14);                        // GPIO15 is XINT4
    XintRegs.XINT4CR.bit.POLARITY = 0;              // Falling edge interrupt
    XintRegs.XINT4CR.bit.ENABLE = 1;                // Enable XINT1
}
