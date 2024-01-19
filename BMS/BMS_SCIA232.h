/*
 * BMS_SCIA232.h
 *
 *  Created on: 2023-11-09
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This is communication system for RS232 port
 */

#ifndef BMS_BMS_SCIA232_H_
#define BMS_BMS_SCIA232_H_

unsigned    char        COMM_Type = 0x00;
unsigned    char        flag_break = 0;
unsigned    char        SysState_temp = 0;
unsigned    char        ChargeMode_temp = 0;

#include    "BMS_struct.h"


extern      enum        SYS_STATE                   SysState;
extern      enum        CHARGE_MODE                 ChargeMode;
extern      struct      Slot                        Slot_1,
                                                    Slot_2,
                                                    Slot_3;

#define                 COMM_Default                0x00
#define                 COMM_Start                  0x01
#define                 COMM_Feedback               0x02
#define                 COMM_Command                0x03
#define                 COMM_SysState               0x04
#define                 COMM_ChargeMode             0x05


void Init_COMM(void);
void scia_echoback_init(void);
void scia_fifo_init(void);
void SCIA_232_GPIO(void);
void update (void);
void process (void);
void scia_xmit(unsigned char);
unsigned char scia_rxmit (void);
float float_rxmit(void);
void float_xmit(float num);
void Send_Feedback (void);

#endif /* BMS_BMS_SCIA232_H_ */
