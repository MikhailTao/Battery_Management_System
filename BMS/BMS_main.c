/*
 * BMS_main.c
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This is interrupt service routine for ADC
 */

#include "F2837xD_Cla_typedefs.h"  // F2837xD CLA Type definitions
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

    // Enable TINT0 in the PIE: Group 10 interrupt 2  对应ADC pin2

    IER |= M_INT1;                                  //打开第一组中断

    EALLOW;
    PieVectTable.ADCA1_INT = &ISR;                  //function for ADCA interrupt 1  连接ADCA pin0
    EDIS;

    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;              //对应1.1组

    InitADC();                                      //Initialize ADC
    PWM_Init();                                     //Initialize EPWM

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
