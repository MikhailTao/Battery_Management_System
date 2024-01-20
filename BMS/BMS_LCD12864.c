/*
 * BMS_LCD12864.c
 *
 *  Created on: 2024-01-19
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: LCD source file
 */

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "BMS_LCD12864.h"

void LCD_GPIO(void)
{
    GPIO_SetupPinMux(53, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(53, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(56, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(56, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(57, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(57, GPIO_OUTPUT, GPIO_PUSHPULL);
}


void Init_LCD(void)
{
    LCD_GPIO();

    Init_Emif1();

    RS=0;
    delay(5);
    RW=0;
    delay(5);
    EN=0;

    DELAY_US(5000);
    Write_order(0x30);// 功能设定：基本指令动作
    DELAY_US(50);
    Write_order(0x0c);//显示状态：开
    DELAY_US(50);
    Write_order(0x01);//清屏
    DELAY_US(60);
    Write_order(0x02);//地址归位：AC=0x00
    DELAY_US(40);
}

void display(unsigned char *hz)
{
    while(*hz!='\0')
    {
        Write_data(*hz);
        hz++;
        DELAY_US(250);
    }
}

void display_state (void){
    Write_order(0x01);

    delay(50);
    Write_order(0x88);
    delay(5);
    Write_data(0xff);
    DELAY_US(250);

    Write_order(0x90);
    delay(5);
    Write_data(0xaa);
    DELAY_US(250);
}


void Write_order(Uint16 order)
{
    RS=0;delay(1);
    RW=0;delay(1);
    EN=1;delay(1);
    LCD_DATA(order);
    EN=0;delay(1);
}

void Write_data(Uint16 data)
{
    RS=1;delay(1);
    RW=0;delay(1);
    EN=1;delay(1);
    LCD_DATA(data);
    EN=0;delay(1);
}

void delay(Uint16 t)
{
    Uint16 i;
    while(t--)
    {
        for(i=0;i<500;i++);
    }
}

void LCD_DATA(unsigned char d)
{
    LCD_DATA_BUS = d;
}

void Init_Emif1(void)
{
    Uint16 ErrCount = 0,i = 0;
    for (i=31; i<=52;i++)
    {
        if (i != 42 || i != 43 || i != 29 || i != 30 || i != 32 || i != 36)
        {
            GPIO_SetupPinMux(i,0,2);
        }
    }
    for (i=69; i<=87;i++)
    {
        if (i != 84)
        {
            GPIO_SetupPinMux(i,0,2);
        }
    }
    GPIO_SetupPinMux(88,0,2);
    GPIO_SetupPinMux(89,0,2);
    GPIO_SetupPinMux(90,0,2);
    GPIO_SetupPinMux(91,0,2);
    GPIO_SetupPinMux(92,0,3);
    GPIO_SetupPinMux(93,0,3);
    GPIO_SetupPinMux(94,0,2);

    //setup async mode and enable pull-ups for Data pins
    for (i=69; i<=85;i++)
    {
        if (i != 84)
        {
            GPIO_SetupPinOptions(i,0,0x31); // GPIO_ASYNC||GPIO_PULLUP
        }
    }
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EMIF1CLKDIV = 0x0;
    EDIS;
    EALLOW;
    //Disable Access Protection (CPU_FETCH/CPU_WR/DMA_WR)
    Emif1ConfigRegs.EMIF1ACCPROT0.all = 0x0;
    if (Emif1ConfigRegs.EMIF1ACCPROT0.all != 0x0)
    {
        ErrCount++;
    }

    // Commit the configuration related to protection. Till this bit remains set
    // content of EMIF1ACCPROT0 register can't be changed.
    Emif1ConfigRegs.EMIF1COMMIT.all = 0x1;
    if(Emif1ConfigRegs.EMIF1COMMIT.all != 0x1)
    {
        ErrCount++;
    }

    // Lock the configuration so that EMIF1COMMIT register can't be changed any more.
    Emif1ConfigRegs.EMIF1LOCK.all = 0x1;
    if (Emif1ConfigRegs.EMIF1LOCK.all != 1)
    {
        ErrCount++;
    }

    EDIS;
    Emif1Regs.ASYNC_CS2_CR.bit.ASIZE = 1;  // 1:0 Asynchronous Memory Size.
    Emif1Regs.ASYNC_CS2_CR.bit.TA= 3;          // 3:2 Turn Around cycles.
    Emif1Regs.ASYNC_CS2_CR.bit.R_HOLD= 5;           // 6:4 Read Strobe Hold cycles.
    Emif1Regs.ASYNC_CS2_CR.bit.R_STROBE = 9;      // 12:7 Read Strobe Duration cycles.
    Emif1Regs.ASYNC_CS2_CR.bit.R_SETUP = 5;             // 16:13 Read Strobe Setup cycles.
    Emif1Regs.ASYNC_CS2_CR.bit.W_HOLD = 5;               // 19:17 Write Strobe Hold cycles.
    Emif1Regs.ASYNC_CS2_CR.bit.W_STROBE = 9;           // 25:20 Write Strobe Duration cycles.
    Emif1Regs.ASYNC_CS2_CR.bit.W_SETUP  = 5;            // 29:26 Write Strobe Setup cycles.
    Emif1Regs.ASYNC_CS2_CR.bit.EW = 0;              // 30 Extend Wait mode.
    Emif1Regs.ASYNC_CS2_CR.bit.SS = 0;               // 31 Select Strobe mode.

    Emif1Regs.ASYNC_CS3_CR.bit.ASIZE = 1;      // 1:0 Asynchronous Memory Size.
    Emif1Regs.ASYNC_CS3_CR.bit.TA= 3;              // 3:2 Turn Around cycles.
    Emif1Regs.ASYNC_CS3_CR.bit.R_HOLD= 5;               // 6:4 Read Strobe Hold cycles.
    Emif1Regs.ASYNC_CS3_CR.bit.R_STROBE = 9;          // 12:7 Read Strobe Duration cycles.
    Emif1Regs.ASYNC_CS3_CR.bit.R_SETUP = 5;                 // 16:13 Read Strobe Setup cycles.
    Emif1Regs.ASYNC_CS3_CR.bit.W_HOLD = 5;                   // 19:17 Write Strobe Hold cycles.
    Emif1Regs.ASYNC_CS3_CR.bit.W_STROBE = 9;               // 25:20 Write Strobe Duration cycles.
    Emif1Regs.ASYNC_CS3_CR.bit.W_SETUP  = 5;                // 29:26 Write Strobe Setup cycles.
    Emif1Regs.ASYNC_CS3_CR.bit.EW = 0;                  // 30 Extend Wait mode.
    Emif1Regs.ASYNC_CS3_CR.bit.SS = 0;                   // 31 Select Strobe mode.

    Emif1Regs.ASYNC_CS4_CR.bit.ASIZE =1;      // 1:0 Asynchronous Memory Size.
    Emif1Regs.ASYNC_CS4_CR.bit.TA= 3;              // 3:2 Turn Around cycles.
    Emif1Regs.ASYNC_CS4_CR.bit.R_HOLD= 5;               // 6:4 Read Strobe Hold cycles.
    Emif1Regs.ASYNC_CS4_CR.bit.R_STROBE =9;          // 12:7 Read Strobe Duration cycles.
    Emif1Regs.ASYNC_CS4_CR.bit.R_SETUP = 5;                 // 16:13 Read Strobe Setup cycles.
    Emif1Regs.ASYNC_CS4_CR.bit.W_HOLD    =5;                   // 19:17 Write Strobe Hold cycles.
    Emif1Regs.ASYNC_CS4_CR.bit.W_STROBE =9;               // 25:20 Write Strobe Duration cycles.
    Emif1Regs.ASYNC_CS4_CR.bit.W_SETUP   = 5;                // 29:26 Write Strobe Setup cycles.
    Emif1Regs.ASYNC_CS4_CR.bit.EW = 0;                  // 30 Extend Wait mode.
    Emif1Regs.ASYNC_CS4_CR.bit.SS = 0;                   // 31 Select Strobe mode.
}
