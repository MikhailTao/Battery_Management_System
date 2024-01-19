/*
 * BMS_VAR.h
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This file stores all external reference to BMS fundamental settings
 */

#ifndef BMS_BMS_EXT_H_
#define BMS_BMS_EXT_H_

//  ADC
extern          float           ADC_Convert_Offset_0,
                                ADC_Convert_Offset_1,
                                ADC_Convert_Offset_2,
                                ADC_Convert_Offset_3;
extern          float           ADC_0, ADC_1, ADC_2, ADC_3;

//  ePWM
extern          int             tbprd;
extern          float           Ts;

//  System Control
#include        "BMS_enum.h"
#include        "BMS_struct.h"
extern          enum            SYS_STATE       SysState;
extern          enum            CHARGE_MODE     ChargeMode;
extern          enum            SLOT_SELECT     Slot_Select;
extern          enum            BUTTON_PRESS    Button_Press;

extern          struct          Slot            Slot_1,Slot_2,Slot_3;
extern          union           CharFloat       Float_Char_Convert;

extern          float           Kp;
extern          float           Ki;
extern          float           Kd;

//  Data
extern          float           Data_Center_3[3000],
                                Data_Center_4[3000];

// Feedback Package
extern  unsigned    char        Data_Sample_Cycle_Count;
extern  unsigned    char        flag_data_center_ready;
extern  unsigned    char        Data_Center_3_Ready;                        // DC3 Ready for transmission?
extern  unsigned    char        Data_Center_4_Ready;                        // DC4 Ready for transmission?
extern  unsigned    char        Data_Package_Select;                        // DC3_save_DC4_transmit or
extern  unsigned    char        Data_Package_Transmission;                  // In transmission?
extern  unsigned    int         Feedback_Package_Index;                     // 0~1000
extern  const       int         Data_Package_Size;
extern  const       int         Data_Sample_Cycle;

#define                 NotReady                    0
#define                 Ready                       1
#define                 DC3_save_DC4_transmit       0
#define                 DC3_transmit_DC4_save       1
#define                 Wait_For_Data               0
#define                 In_Transmission             1                       // Lock the current Data Center


#endif /* BMS_BMS_EXT_H_ */
