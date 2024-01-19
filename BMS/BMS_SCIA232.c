/*
 * BMS_SCIA232.c
 *
 *  Created on: 2023-11-03
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This is communication system for RS232 port
 */

#include "F2837xD_device.h"
#include "BMS_SCIA232.h"
#include "BMS_Ext.h"

// update communication type
void update (void){
    if (SciaRegs.SCIFFRX.bit.RXFFST != 0) {
        COMM_Type = SciaRegs.SCIRXBUF.all;                                          // wait for XRDY =1 for empty stateGet character
        process();                                                                  // Response
    }
}

// response base on the communication type
void process (void){
    switch (COMM_Type){
    case    COMM_Start:
        // Hello
        scia_xmit (COMM_Start);
        scia_rxmit();                                                               // Wait for APP ready response
        SysState == ON? scia_xmit(0x01):scia_xmit(0x00);
        ChargeMode == Fast? scia_xmit(0x00):scia_xmit(0x01);
        float_xmit(Kp);
        float_xmit(Ki);
        float_xmit(Kd);
        break;
    case    COMM_Feedback:
        // Send Feedback to APP
        scia_xmit(COMM_Feedback);
        scia_rxmit();                                                               // Wait for APP ready response
        Send_Feedback();
        break;
    case    COMM_Command:
        // Receive Command from APP
        scia_xmit(COMM_Command);
        Kp = float_rxmit();
        Ki = float_rxmit();
        Kd = float_rxmit();
        break;
    case    COMM_SysState:
        // System State
        scia_xmit(COMM_SysState);
        SysState_temp = scia_rxmit();
        if (SysState_temp == 0){
            SysState = OFF;
        }else{
            SysState = ON;
        }
        break;
    case    COMM_ChargeMode:
        // Charging Mode
        scia_xmit(COMM_ChargeMode);
        ChargeMode_temp = scia_rxmit();
        if (ChargeMode_temp == 0){
            ChargeMode = Fast;
        }else{
            ChargeMode = Balance;
        }
        break;
    default:
        // Do Nothing
        break;
    }
}

// Send Feedback
void Send_Feedback (void){
    int counter = 0;

    while(1){
        if ((Data_Package_Select == DC3_transmit_DC4_save) && (Data_Center_3_Ready == Ready)){
            break;
        }
        if ((Data_Package_Select == DC3_save_DC4_transmit) && (Data_Center_4_Ready == Ready)){
            break;
        }
    }

    if((Data_Package_Select == DC3_transmit_DC4_save) && (Data_Center_3_Ready == Ready)){
        Data_Package_Transmission = In_Transmission;
        for (counter = 0; counter < Data_Package_Size*3; counter++){
            float_xmit(Data_Center_3[counter]);
        }
        Data_Package_Transmission = Wait_For_Data;
        Data_Center_3_Ready = NotReady;
    } else if((Data_Package_Select == DC3_save_DC4_transmit) && (Data_Center_4_Ready == Ready)){
        Data_Package_Transmission = In_Transmission;
        for (counter = 0; counter < Data_Package_Size*3; counter++){
            float_xmit(Data_Center_4[counter]);
        }
        Data_Package_Transmission = Wait_For_Data;
        Data_Center_4_Ready = NotReady;
    }
}


void float_xmit (float data){
    Float_Char_Convert.Value = data;                            // extract data
    scia_xmit((Float_Char_Convert.str[0] & 0x00ff));            // byte 1
    scia_xmit((Float_Char_Convert.str[0] & 0xff00)>>8);         // byte 2
    scia_xmit(Float_Char_Convert.str[1] & 0x00ff);              // byte 3
    scia_xmit((Float_Char_Convert.str[1] & 0xff00)>>8);         // byte 4
}

float float_rxmit (){
    unsigned int byte1, byte2, byte3, byte4;
    byte1 = scia_rxmit();
    byte2 = scia_rxmit();
    byte3 = scia_rxmit();
    byte4 = scia_rxmit();
    Float_Char_Convert.str[0] = (byte2<<8) + byte1;
    Float_Char_Convert.str[1] = (byte4<<8) + byte3;
    return Float_Char_Convert.Value;
}

// COMM Initiate Setting
void Init_COMM() {
    SCIA_232_GPIO();
    scia_fifo_init();        // Initialize the SCI FIFO
    scia_echoback_init();    // Initialize SCI for echoback
}

// Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity
void scia_echoback_init()
{
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function

    SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
    // No parity,8 char bits,
    // async mode, idle-line protocol
    SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
    // Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.all =0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA =1;
    SciaRegs.SCICTL2.bit.RXBKINTENA =1;

    //
    // SCIA at 9600 baud
    // @LSPCLK = 50 MHz (200 MHz SYSCLK) HBAUD = 0x02 and LBAUD = 0x8B.
    // @LSPCLK = 30 MHz (120 MHz SYSCLK) HBAUD = 0x01 and LBAUD = 0x86.

    // SCI Asynchronous Baud = LSPCLK / ((BRR + 1) *8)
    // Baud = 312500 => 19 => 0x13
    // SciaRegs.SCIHBAUD.all    =0x0002;
    // SciaRegs.SCILBAUD.all    =0x008B;
    SciaRegs.SCIHBAUD.all    =0x0000;
    SciaRegs.SCILBAUD.all    =0x0013;

    SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
}

// Initialize the SCI FIFO
void scia_fifo_init()
{
    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x2044;
    SciaRegs.SCIFFCT.all=0x0;
}

// Transmit a character from the SCI
void scia_xmit(unsigned char a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}//0h (R/W) = Transmit FIFO is empty
    SciaRegs.SCITXBUF.all =a;
}

// Receive a character from the SCI
unsigned char scia_rxmit (void){
    // Wait for character
    while(SciaRegs.SCIFFRX.bit.RXFFST == 0) { } // wait for XRDY =1 for empty state
    // Get character
    return SciaRegs.SCIRXBUF.all;
}

// GPIO INITIALIZATION
void SCIA_232_GPIO(void){
    EALLOW;
    GpioCtrlRegs.GPCMUX1.bit.GPIO64 = 2;
    GpioCtrlRegs.GPCMUX1.bit.GPIO65 = 2;
    GpioCtrlRegs.GPCGMUX1.bit.GPIO64 = 1;
    GpioCtrlRegs.GPCGMUX1.bit.GPIO65 = 1;
    EDIS;
}
