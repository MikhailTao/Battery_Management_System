/*
 * BMS_main.c
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This is main function
 */



#include "F2837xD_device.h"                                     // F2837xD Header file Include File
#include "F2837xD_Examples.h"                                   // F2837xD Examples Include File
#include "F2837xD_Ipc_drivers.h"
#include "BMS_main.h"



void main(void)
{
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2837xD_SysCtrl.c file.
    InitSysCtrl();

#ifdef _STANDALONE
#ifdef _FLASH
    // Send boot command to allow the CPU2 application to begin execution
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else
    // Send boot command to allow the CPU2 application to begin execution
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif
    // Call Flash Initialization to setup flash waitstates
    // This function must reside in RAM
#ifdef _FLASH
    InitFlash();
#endif

    // Step 2. Initialize GPIO:
    // This example function is found in the F2837xD_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    InitGpio();

    Init_ADC();                                                 // Initialize ADC
    Init_PWM();                                                 // Initialize EPWM
    Init_Exint();                                               // Initialize Button
    Init_COMM();                                                // Initialize SCIA-RS232 communication
    Init_LCD();                                                 // Initialize LCD 12864
    Init_LED();                                                 // Initialize LED

    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    DINT;

    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the F2837xD_PieCtrl.c file.
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2837xD_DefaultIsr.c.
    // This function is found in F2837xD_PieVect.c.
    InitPieVectTable();

    EINT;                                                       // Enable Global interrupt INTM
    ERTM;                                                       // Enable Global real-time interrupt DBGM

    EPwm1Regs.ETSEL.bit.INTSEL = 1;                             // when TBCTR = 0£¬trigger EPWM1_INI
    EPwm1Regs.ETPS.bit.INTPRD = 1;                              // Generate INT on 1st event
    EPwm1Regs.ETCLR.bit.INT = 1;                                // Clear Interrupt Flag ETFLG.INT = 0
    EPwm1Regs.ETSEL.bit.INTEN = 1;                              // Enable INT

    IER |= M_INT3;                                              // PWM1
    IER |= M_INT1;                                              // Button 1, Button 2
//    IER |= M_INT12;                                             // Button 3, Button 4

    EALLOW;
    PieVectTable.EPWM1_INT = &ISR;                              // ISR function for EPWM1 interrupt
    PieVectTable.XINT1_INT = &xint1_isr;                        // Button 1 External Interrupt
    PieVectTable.XINT2_INT = &xint2_isr;                        // Button 2 External Interrupt
//    PieVectTable.XINT3_INT = &xint3_isr;                        // Button 3 External Interrupt
//    PieVectTable.XINT4_INT = &xint4_isr;                        // Button 4 External Interrupt
    EDIS;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;                          // Enable the PIE block
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;                          // Enable PIE Group 3 INT1      PWM1
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;                          // Enable PIE Group 1 INT4      Button XINT1
    PieCtrlRegs.PIEIER1.bit.INTx5 = 1;                          // Enable PIE Group 1 INT5      Button XINT2
//    PieCtrlRegs.PIEIER12.bit.INTx1 = 1;                         // Enable PIE Group 12 INT1     Button XINT3
//    PieCtrlRegs.PIEIER12.bit.INTx2 = 1;                         // Enable PIE Group 12 INT2     Button XINT4

    Init_Slot();
    Init_BMS ();

    display_state();

    while(1)
    {
        update();
    }
}

void Init_BMS (void){
    SysState = OFF;
    ChargeMode = Fast;

    Kp = 0;
    Ki = 0;
    Kd = 0;

    int i = 0;
    for (i = 0; i < sizeof(Data_Center_3)/2; i++){
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

void Init_Slot (void){
    Init_Slot_single(&Slot_1);
    Init_Slot_single(&Slot_2);
    Init_Slot_single(&Slot_3);
}

void Init_Slot_single(struct Slot* s){
    s->BatteryState = None;
    s->Diff_Voltage = 0.0f;
    s->DutyRatio = 0.0f;
    s->Volatge = 0.0f;
    s->Reff_Voltage = 15.0f;                // 15V
    s->Error = 0.0f;
    s->PrevError = 0.0f;
    s->Derivative = 0.0f;
    s->Integral = 0.0f;
}
