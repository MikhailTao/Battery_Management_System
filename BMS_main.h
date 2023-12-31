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
int     tbprd = 10000;                                                      // ePWM period length 200e6Hz/1e5Hz
const       float       Ts = 10000/100e6;                                   // Cycle time
//  System Control
float   Kp = 0.0f;
float   Ki = 0.0f;
float   Kd = 0.0f;

float   const   Max_Putput_Voltage = 15.0f;

#include "BMS_enum.h"
enum    SYS_STATE       SysState = OFF;
enum    CHARGE_MODE     ChargeMode = Fast;
enum    SLOT_SELECT     Slot_Select = Slot1;
enum    BUTTON_PRESS    Button_Press = Short_Press;

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

// LED
#define LED1_ON  GpioDataRegs.GPASET.bit.GPIO0 = 1
#define LED1_OFF GpioDataRegs.GPACLEAR.bit.GPIO0 = 1
#define LED2_ON  GpioDataRegs.GPASET.bit.GPIO1 = 1
#define LED2_OFF GpioDataRegs.GPACLEAR.bit.GPIO1 = 1
#define LED3_ON  GpioDataRegs.GPASET.bit.GPIO2 = 1
#define LED3_OFF GpioDataRegs.GPACLEAR.bit.GPIO2 = 1
#define LED4_ON  GpioDataRegs.GPASET.bit.GPIO3 = 1
#define LED4_OFF GpioDataRegs.GPACLEAR.bit.GPIO3 = 1
#define LED5_ON  GpioDataRegs.GPASET.bit.GPIO4 = 1
#define LED5_OFF GpioDataRegs.GPACLEAR.bit.GPIO4 = 1
#define LED6_ON  GpioDataRegs.GPASET.bit.GPIO5 = 1
#define LED6_OFF GpioDataRegs.GPACLEAR.bit.GPIO5 = 1

// SEG_7
#define   SBIT3     GpioDataRegs.GPBDAT.bit.GPIO58
#define   SBIT2     GpioDataRegs.GPBDAT.bit.GPIO59
#define   SBIT1     GpioDataRegs.GPBDAT.bit.GPIO60
#define   SBIT0     GpioDataRegs.GPBDAT.bit.GPIO61

unsigned char const seg7_table[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6};

//////////////////////////////////////////////////////////////////////
//                      Function Declaration                        //
//////////////////////////////////////////////////////////////////////
void BMS_Init (void);
void Slot_Init (void);
void ExintInit(void);
void LED_GPIO_Setup(void);
//  Control

//  ADC
extern void SetupADC(void);
extern void InitADC(void);
//  ePWM
extern void PWM_Init(void);
// ISR
extern void ISR(void);
// SCIA-RS232
extern void SCIA_232_GPOI(void);
extern void COMM_Init(void);
extern void convert_transmit(float);
extern float convert_receive (void);
extern void scia_xmit(unsigned char a);
extern unsigned char scia_rxmit(void);
extern void update (void);
//External Interrupt
extern void xint1_isr(void);
extern void xint2_isr(void);
extern void xint3_isr(void);
extern void xint4_isr(void);
// SEG_7
extern void SEG7_Display(void);
extern void SEG7_GPIO(void);

#endif
