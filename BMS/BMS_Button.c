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
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    DELAY_US(500);
    if(GpioDataRegs.GPADAT.bit.GPIO13 == 0){
        if (SysState == ON) SysState = OFF;
        else SysState = ON;
    }
}

interrupt void xint2_isr(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    DELAY_US(500);
    if(GpioDataRegs.GPADAT.bit.GPIO12 == 0){
        if (ChargeMode == Fast) ChargeMode = Balance;
        else ChargeMode = Fast;
    }
}
