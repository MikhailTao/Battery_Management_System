/*
 * BMS_EPWM.c
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This file stores ePWM settings
 */

#include "F2837xD_device.h"        // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"      // F2837xD Examples Include File
#include "BMS_ePWM.h"

void PWM_Init(){
    EPWM1_Init();
    EPWM2_Init();
    EPWM3_Init();
    EPWM4_Init();
}

void EPWM1_Init()
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;                       // Disable TBCLK within the ePWM
    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;                           // ePWM1
    EDIS;

    InitEPwm1Gpio();//开启 ePWM 对应 GPIO 时钟及初始化配置

    // 初始化时基模块，即配置 TB 相关寄存器值
    EPwm1Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // 时基周期立即加载模式
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  时钟不同步

    // Allow each timer to be sync'ed
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //使用相位同步功能
    EPwm1Regs.TBPHS.all = 0;                                    //相位寄存器清零
    EPwm1Regs.TBCTR = 0x0000;                                   // 清除计数器的值
    EPwm1Regs.TBPRD = tbprd;                                    // 周期频率
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // 为向上计数
    EPwm1Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // 时钟不分频

    // 初始化比较模块，即配置 CC 相关寄存器值
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // 加载方式为计数器为 0 加载
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // 影子寄存器

    // 设置比较器值
    EPwm1Regs.CMPA.bit.CMPA = 0;                                // Set Duty Ratio to 0 at beginning

    // 初始化动作限定模块，即配置 AQ 相关寄存器值
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm1Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm1Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //初始化事件触发模块，即配置 ET 相关寄存器值
    EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;                  // ADCSOCA on TBCTR= zero
    EPwm1Regs.ETPS.bit.SOCAPRD = ET_1ST;                        // Generate SOCA on 1st event
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;                             // Enable SOCA generation

    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm1Regs.DBRED.all = 0;                                    //Dead Band 0
    EPwm1Regs.DBFED.all = 0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;                       // Start all the timers synced
    EDIS;
}

void EPWM2_Init()
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;                       // Disable TBCLK within the ePWM
    CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;                           // ePWM2
    EDIS;

    InitEPwm2Gpio();                                            //开启 ePWM 对应 GPIO 时钟及初始化配置

    // 初始化时基模块，即配置 TB 相关寄存器值
    EPwm2Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // 时基周期立即加载模式
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  时钟不同步

    // Allow each timer to be sync'ed
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //使用相位同步功能
    EPwm2Regs.TBPHS.all = 0;                                    //相位寄存器清零
    EPwm2Regs.TBCTR = 0x0000;                                   // 清除计数器的值
    EPwm2Regs.TBPRD = tbprd;                                    // 周期频率
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // 为向上计数
    EPwm2Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm2Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // 时钟不分频

    // 初始化比较模块，即配置 CC 相关寄存器值
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // 加载方式为计数器为 0 加载
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // 影子寄存器

    // 设置比较器值
    EPwm2Regs.CMPA.bit.CMPA = tbprd/2;                          // Set compare A value 比较器值为 0

    // 初始化动作限定模块，即配置 AQ 相关寄存器值
    EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm2Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm2Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //初始化事件触发模块，即配置 ET 相关寄存器值
    EPwm2Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;                  // ADCSOCA on TBCTR= zero
    EPwm2Regs.ETPS.bit.SOCAPRD = ET_1ST;                        // Generate SOCA on 1st event
    EPwm2Regs.ETSEL.bit.SOCAEN = 1;                             // Enable SOCA generation

    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm2Regs.DBRED.all = 0;                                    //Dead Band 0
    EPwm2Regs.DBFED.all = 0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;                       // Start all the timers synced
    EDIS;
}

void EPWM3_Init()
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;                       // Disable TBCLK within the ePWM
    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;                           // ePWM3
    EDIS;

    InitEPwm3Gpio();//开启 ePWM 对应 GPIO 时钟及初始化配置

    // 初始化时基模块，即配置 TB 相关寄存器值
    EPwm3Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // 时基周期立即加载模式
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  时钟不同步

    // Allow each timer to be sync'ed
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //使用相位同步功能
    EPwm3Regs.TBPHS.all = 0;                                    //相位寄存器清零
    EPwm3Regs.TBCTR = 0x0000;                                   // 清除计数器的值
    EPwm3Regs.TBPRD = tbprd;                                    // 周期频率
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // 为向上计数
    EPwm3Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm3Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // 时钟不分频

    // 初始化比较模块，即配置 CC 相关寄存器值
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // 加载方式为计数器为 0 加载
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // 影子寄存器

    // 设置比较器值
    EPwm3Regs.CMPA.bit.CMPA = 0;                                // Set Duty Ratio to 0 at beginning

    // 初始化动作限定模块，即配置 AQ 相关寄存器值
    EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm3Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm3Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //初始化事件触发模块，即配置 ET 相关寄存器值
    EPwm3Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;                  // ADCSOCA on TBCTR= zero
    EPwm3Regs.ETPS.bit.SOCAPRD = ET_1ST;                        // Generate SOCA on 1st event
    EPwm3Regs.ETSEL.bit.SOCAEN = 1;                             // Enable SOCA generation

    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm3Regs.DBRED.all = 0;                                    //Dead Band 0
    EPwm3Regs.DBFED.all = 0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;                       // Start all the timers synced
    EDIS;
}

void EPWM4_Init()
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;                       // Disable TBCLK within the ePWM
    CpuSysRegs.PCLKCR2.bit.EPWM4 = 1;                           // ePWM4
    EDIS;

    InitEPwm4Gpio();                                            //开启 ePWM 对应 GPIO 时钟及初始化配置

    // 初始化时基模块，即配置 TB 相关寄存器值
    EPwm4Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // 时基周期立即加载模式
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  时钟不同步

    // Allow each timer to be sync'ed
    EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //使用相位同步功能
    EPwm4Regs.TBPHS.all = 0;                                    //相位寄存器清零
    EPwm4Regs.TBCTR = 0x0000;                                   // 清除计数器的值
    EPwm4Regs.TBPRD = tbprd;                                    // 周期频率
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // 为向上计数
    EPwm4Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm4Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // 时钟不分频

    // 初始化比较模块，即配置 CC 相关寄存器值
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // 加载方式为计数器为 0 加载
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // 影子寄存器

    // 设置比较器值
    EPwm4Regs.CMPA.bit.CMPA = tbprd/2;                          // Set compare A value 比较器值为 0

    // 初始化动作限定模块，即配置 AQ 相关寄存器值
    EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm4Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm4Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //初始化事件触发模块，即配置 ET 相关寄存器值
    EPwm4Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;                  // ADCSOCA on TBCTR= zero
    EPwm4Regs.ETPS.bit.SOCAPRD = ET_1ST;                        // Generate SOCA on 1st event
    EPwm4Regs.ETSEL.bit.SOCAEN = 1;                             // Enable SOCA generation

    EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm4Regs.DBRED.all = 0;                                    //Dead Band 0
    EPwm4Regs.DBFED.all = 0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;                       // Start all the timers synced
    EDIS;
}
