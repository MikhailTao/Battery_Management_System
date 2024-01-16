/*
 * BMS_main.c
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This is main function
 */



#include "F2837xD_device.h"                         // F2837xD Header file Include File
#include "F2837xD_Examples.h"                       // F2837xD Examples Include File
#include "BMS_main.h"



void main(void)
{
    InitSysCtrl();

#ifdef _FLASH
    InitFlash();
#endif

    InitGpio();

    InitADC();                                      // Initialize ADC
    PWM_Init();                                     // Initialize EPWM
    SCIA_232_GPIO();

    DINT;

    InitPieCtrl();

    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

    EINT;                                           // Enable Global interrupt INTM
    ERTM;                                           // Enable Global real-time interrupt DBGM

    EPwm1Regs.ETSEL.bit.INTSEL = 1;                 // when TBCTR = 0£¬trigger EPWM1_INI
    EPwm1Regs.ETPS.bit.INTPRD = 1;                  // Generate INT on 1st event
    EPwm1Regs.ETCLR.bit.INT = 1;                    // Clear Interrupt Flag ETFLG.INT = 0
    EPwm1Regs.ETSEL.bit.INTEN = 1;                  // Enable INT

    IER |= M_INT3;                                  // PWM1

    EALLOW;
    PieVectTable.EPWM1_INT = &ISR;                  // ISR function for EPWM1 interrupt
    EDIS;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;              // Enable the PIE block
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;              // Enable PIE Group 3 INT1      PWM1

//    Slot_Init();
    COMM_Init();                                    // Initialize SCIA-RS232 communication
//    BMS_Init ();

    SysState = OFF;
    ChargeMode = Fast;

//    Kp = 0;
//    Ki = 0;
//    Kd = 0;

//    int i = 0;
//    for (i = 0; i < Data_Package_Size*6; i++){
//        Data_Center_3[i] = 0;
//        Data_Center_4[i] = 0;
//    }

//    Data_Sample_Cycle_Count = 0;
//    flag_data_center_ready = 0;
//    Data_Center_3_Ready = 0;
//    Data_Center_4_Ready = 0;
//    Data_Package_Select = 0;
//    Data_Package_Transmission = 0;
//    Feedback_Package_Index = 0;

    while(1)
    {
        update();
    }
}

void BMS_Init (void){
    int i = 0;
    for (i = 0; i < Data_Package_Size*6; i++){
        Data_Center_3[i] = 0;
        Data_Center_4[i] = 0;
    }

    Data_Sample_Cycle_Count = 0;
    flag_data_center_ready = 0;
    Data_Center_3_Ready = 0;
    Data_Center_4_Ready = 0;
    Data_Package_Select = 0;
    Data_Package_Transmission = 0;
    Feedback_Package_Index = 0;
}
