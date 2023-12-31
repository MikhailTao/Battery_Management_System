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
#include "F2837xD_Ipc_drivers.h"
#include "BMS_Ext.h"
#include "BMS_Button.h"

interrupt void xint1_isr(void)
{
    unsigned int press_count = 0;
    Button_Press = Short_Press;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    DELAY_US(10000);
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

interrupt void xint3_isr(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    DELAY_US(10000);
    if(GpioDataRegs.GPADAT.bit.GPIO15 == 0){
        if (Slot_Select == Slot1){
            if (Slot_1.Reff_Voltage == Max_Putput_Voltage) Slot_1.Reff_Voltage = 0;
            else Slot_1.Reff_Voltage = Slot_1.Reff_Voltage + Voltage_Step;
        }
        else if (Slot_Select == Slot2){
            if (Slot_2.Reff_Voltage == Max_Putput_Voltage) Slot_2.Reff_Voltage = 0;
            else Slot_2.Reff_Voltage = Slot_2.Reff_Voltage + Voltage_Step;
        }
        else{
            if (Slot_3.Reff_Voltage == Max_Putput_Voltage) Slot_3.Reff_Voltage = 0;
            else Slot_3.Reff_Voltage = Slot_3.Reff_Voltage + Voltage_Step;
        }
    }
}

interrupt void xint4_isr(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    DELAY_US(10000);
    if(GpioDataRegs.GPADAT.bit.GPIO14 == 0){
        if (Slot_Select == Slot1){
            if (Slot_1.Reff_Voltage == 0) Slot_1.Reff_Voltage = Max_Putput_Voltage;
            else Slot_1.Reff_Voltage = Slot_1.Reff_Voltage - Voltage_Step;
        }
        else if (Slot_Select == Slot2){
            if (Slot_2.Reff_Voltage == 0) Slot_2.Reff_Voltage = Max_Putput_Voltage;
            else Slot_2.Reff_Voltage = Slot_2.Reff_Voltage - Voltage_Step;
        }
        else{
            if (Slot_3.Reff_Voltage == 0) Slot_3.Reff_Voltage = Max_Putput_Voltage;
            else Slot_3.Reff_Voltage = Slot_3.Reff_Voltage - Voltage_Step;
        }
    }
}
