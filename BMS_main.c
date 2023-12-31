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
    SCIA_232_GPOI();
    ExintInit();
    LED_GPIO_Setup();
    SEG7_GPIO();

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

    IER |= M_INT1;                                  // Button 1, Button 2
    IER |= M_INT12;                                 // Button 3, Button 4
    IER |= M_INT3;                                  // PWM1

    EALLOW;
    PieVectTable.EPWM1_INT = &ISR;                  // ISR function for EPWM1 interrupt
    PieVectTable.XINT1_INT = &xint1_isr;            // Button 1 External Interrupt
    PieVectTable.XINT2_INT = &xint2_isr;            // Button 2 External Interrupt
    PieVectTable.XINT3_INT = &xint3_isr;            // Button 3 External Interrupt
    PieVectTable.XINT4_INT = &xint4_isr;            // Button 4 External Interrupt
    EDIS;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;              // Enable the PIE block
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;              // Enable PIE Group 3 INT1      PWM1
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;              // Enable PIE Group 1 INT4      Button XINT1
    PieCtrlRegs.PIEIER1.bit.INTx5 = 1;              // Enable PIE Group 1 INT5      Button XINT2
    PieCtrlRegs.PIEIER12.bit.INTx1 = 1;             // Enable PIE Group 12 INT1     Button XINT3
    PieCtrlRegs.PIEIER12.bit.INTx2 = 1;             // Enable PIE Group 12 INT2     Button XINT4

    Slot_Init();
    COMM_Init();                                    // Initialize SCIA-RS232 communication
    BMS_Init ();

    SysState = OFF;
    ChargeMode = Fast;

    Kp = 0;
    Ki = 0;
    Kd = 0;

    LED1_OFF;
    LED2_OFF;
    LED3_OFF;
    LED4_OFF;
    LED5_OFF;
    LED6_OFF;

    SBIT0=0;DELAY_US(1);
    SBIT1=0;DELAY_US(1);
    SBIT2=0;DELAY_US(1);
    SBIT3=0;DELAY_US(1);

    while(1)
    {
        update();
        SEG7_Display();
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

void ExintInit(void){
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

void LED_GPIO_Setup(void){
    GPIO_SetupPinMux(0, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(0, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(1, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(1, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(2, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(2, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(3, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(3, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(4, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(4, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(5, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(5, GPIO_OUTPUT, GPIO_PUSHPULL);
}
