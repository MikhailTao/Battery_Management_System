/*
 * BMS_main.h
 *
 *  Created on: 2023-12-22
 *      Author: Tao Ran
 * Description: This is info center for main
 */

#ifndef BMS_BMS_MAIN_H_
#define BMS_BMS_MAIN_H_

//////////////////////////////////////////////////////////////////////
//                     Parameter Declaration                        //
//////////////////////////////////////////////////////////////////////
//  ePWM
const int     tbprd = 10000;                                                      // ePWM period length 200e6Hz/1e5Hz
const       float       Ts = 10000/100e6;                                   // Cycle time
//  System Control
float   Kp = 0.0f;
float   Ki = 0.0f;
float   Kd = 0.0f;

#include "BMS_enum.h"
enum    SYS_STATE       SysState = OFF;
enum    CHARGE_MODE     ChargeMode = Fast;

#include "BMS_struct.h"
struct  Slot            Slot_1,Slot_2,Slot_3;
union   CharFloat       Float_Char_Convert;

//  Data Collection
const   int             Data_Package_Size = 1000;
const   int             Data_Sample_Cycle = 10;

float                   Data_Center_3[3000],
                        Data_Center_4[3000];

// Feedback Package
unsigned    char        Data_Sample_Cycle_Count = 0;
unsigned    char        flag_data_center_ready = 0;
unsigned    char        Data_Center_3_Ready = 0;                            // DC3 Ready for transmission?
unsigned    char        Data_Center_4_Ready = 0;                            // DC4 Ready for transmission?
unsigned    char        Data_Package_Select = 0;                            // DC3_save_DC4_transmit or
unsigned    char        Data_Package_Transmission = 0;                      // In transmission?
unsigned    int         Feedback_Package_Index = 0;                         // 0~1000

#define                 NotReady                    0
#define                 Ready                       1
#define                 DC3_save_DC4_transmit       0
#define                 DC3_transmit_DC4_save       1
#define                 Wait_For_Data               0
#define                 In_Transmission             1                       // Lock the current Data Center


//////////////////////////////////////////////////////////////////////
//                      Function Declaration                        //
//////////////////////////////////////////////////////////////////////
void BMS_Init (void);
void Slot_Init (void);
//  Control

//  ADC
extern void SetupADC(void);
extern void InitADC(void);
//  ePWM
extern void PWM_Init(void);
// ISR
extern void ISR(void);
// SCIA-RS232
extern void SCIA_232_GPIO(void);
extern void COMM_Init(void);
extern void convert_transmit(float);
extern float convert_receive (void);
extern void scia_xmit(unsigned char a);
extern unsigned char scia_rxmit(void);
extern void update (void);


#endif
