/*
 * BMS_main.c
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This is interrupt service routine for ADC
 */

#include "F2837xD_device.h"        // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"      // F2837xD Examples Include File


//////////////////////////////////////////////////////////////////////
//                      Function Declaration                        //
//////////////////////////////////////////////////////////////////////
void BMS_Config (void);
//  ADC
extern void SetupADC(void);
extern void InitADC(void);
//  ePWM
extern void PWM_Init(void);
// ISR
extern void ISR(void);


//////////////////////////////////////////////////////////////////////
//                          Type Define                             //
//////////////////////////////////////////////////////////////////////
//  System Control
enum    S_STATE {On, Off};
//  Battery Control
enum    B_STATE {None, Charging, Wait, Full};
//  Slot Info
typedef struct  SLOT    {   enum    B_STATE BatteryState;
                            float           Voltage;
                            float           DutyRatio;
                            float           VoltageChangeRate;
} SLOT;

//  Parameters Initialization
enum    S_STATE     SysState = Off;
struct  SLOT        Slot_1 = {None, 0,0,0};
struct  SLOT        Slot_2 = {None, 0,0,0};
struct  SLOT        Slot_3 = {None, 0,0,0};


//////////////////////////////////////////////////////////////////////
//                              CODE                                //
//////////////////////////////////////////////////////////////////////
void main(void)
{
    InitSysCtrl();
    InitGpio();

    DINT;

    InitPieCtrl();

    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

    EINT;                                           // Enable Global interrupt INTM
    ERTM;                                           // Enable Global real-time interrupt DBGM

    InitADC();                                      //Initialize ADC
    PWM_Init();                                     //Initialize EPWM

    // Enable TINT0 in the PIE: Group 10 interrupt 2  对应ADC pin2

    EPwm1Regs.ETSEL.bit.INTSEL = 1;                 // when TBCTR = 0，trigger EPWM1_INI
    EPwm1Regs.ETPS.bit.INTPRD = 1;                  // Generate INT on 1st event
    EPwm1Regs.ETCLR.bit.INT = 1;                    // Clear Interrupt Flag ETFLG.INT = 0
    EPwm1Regs.ETSEL.bit.INTEN = 1;                  // Enable INT

    EALLOW;
    PieVectTable.EPWM1_INT = &ISR;                  //function for EPWM1 interrupt
    EDIS;
    IER |= M_INT3;                                  //打开第一组中断
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;              //对应3.1组

    BMS_Config ();

    while(1)
    {
    }
}

void BMS_Config (void){
    SysState = Off;
    Slot_1.BatteryState = None;
    Slot_2.BatteryState = None;
    Slot_3.BatteryState = None;
}
