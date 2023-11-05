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
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // stop PWM Clock
    EDIS;

    //  Event Trigger Register  -----------------------------------------
    EPwm1Regs.ETSEL.all = 0;               // Initialize
    EPwm1Regs.ETPS.all = 0;
    EPwm1Regs.ETFLG.all = 0;
    EPwm1Regs.ETCLR.all = 0;
    EPwm1Regs.ETFRC.all = 0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;                       // Disable TBCLK within the ePWM
    EDIS;

    EPWM1_Init();
    EPWM2_Init();
    EPWM3_Init();
    EPWM4_Init();
    EPWM5_Init();
    EPWM6_Init();
    EPWM7_Init();
    EPWM8_Init();
    EPWM9_Init();
    EPWM10_Init();
    EPWM11_Init();
    EPWM12_Init();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;                       // Start all the timers synced
    EDIS;
}

void EPWM1_Init()
{
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
    EPwm1Regs.CMPA.bit.CMPA = tbprd/2;                                // Set Duty Ratio to 0 at beginning

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
    EPwm1Regs.DBRED.all = 0;                                    // Dead band Rising edge delay value 0
    EPwm1Regs.DBFED.all = 0;                                    // Dead band Falling Edge Delay Count
}

void EPWM2_Init()
{
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
}

void EPWM3_Init()
{
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
    EPwm3Regs.CMPA.bit.CMPA = tbprd/2;                                // Set Duty Ratio to 0 at beginning

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
}

void EPWM4_Init()
{
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
}

void EPWM5_Init()
{
    InitEPwm5Gpio();                                            //开启 ePWM 对应 GPIO 时钟及初始化配置

    // 初始化时基模块，即配置 TB 相关寄存器值
    EPwm5Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // 时基周期立即加载模式
    EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  时钟不同步

    // Allow each timer to be sync'ed
    EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //使用相位同步功能
    EPwm5Regs.TBPHS.all = 0;                                    //相位寄存器清零
    EPwm5Regs.TBCTR = 0x0000;                                   // 清除计数器的值
    EPwm5Regs.TBPRD = tbprd;                                    // 周期频率
    EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // 为向上计数
    EPwm5Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm5Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // 时钟不分频

    // 初始化比较模块，即配置 CC 相关寄存器值
    EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // 加载方式为计数器为 0 加载
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // 影子寄存器

    // 设置比较器值
    EPwm5Regs.CMPA.bit.CMPA = tbprd/2;                          // Set compare A value 比较器值为 0

    // 初始化动作限定模块，即配置 AQ 相关寄存器值
    EPwm5Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm5Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm5Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //初始化事件触发模块，即配置 ET 相关寄存器值
    EPwm5Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;                  // ADCSOCA on TBCTR= zero
    EPwm5Regs.ETPS.bit.SOCAPRD = ET_1ST;                        // Generate SOCA on 1st event
    EPwm5Regs.ETSEL.bit.SOCAEN = 1;                             // Enable SOCA generation

    EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm5Regs.DBRED.all = 0;                                    //Dead Band 0
    EPwm5Regs.DBFED.all = 0;
}

void EPWM6_Init()
{
    InitEPwm6Gpio();                                            //开启 ePWM 对应 GPIO 时钟及初始化配置

    // 初始化时基模块，即配置 TB 相关寄存器值
    EPwm6Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // 时基周期立即加载模式
    EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  时钟不同步

    // Allow each timer to be sync'ed
    EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //使用相位同步功能
    EPwm6Regs.TBPHS.all = 0;                                    //相位寄存器清零
    EPwm6Regs.TBCTR = 0x0000;                                   // 清除计数器的值
    EPwm6Regs.TBPRD = tbprd;                                    // 周期频率
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // 为向上计数
    EPwm6Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm6Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // 时钟不分频

    // 初始化比较模块，即配置 CC 相关寄存器值
    EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // 加载方式为计数器为 0 加载
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // 影子寄存器

    // 设置比较器值
    EPwm6Regs.CMPA.bit.CMPA = tbprd/2;                          // Set compare A value 比较器值为 0

    // 初始化动作限定模块，即配置 AQ 相关寄存器值
    EPwm6Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm6Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm6Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //初始化事件触发模块，即配置 ET 相关寄存器值
    EPwm6Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;                  // ADCSOCA on TBCTR= zero
    EPwm6Regs.ETPS.bit.SOCAPRD = ET_1ST;                        // Generate SOCA on 1st event
    EPwm6Regs.ETSEL.bit.SOCAEN = 1;                             // Enable SOCA generation

    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm6Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm6Regs.DBRED.all = 0;                                    //Dead Band 0
    EPwm6Regs.DBFED.all = 0;
}

void EPWM7_Init()
{
    InitEPwm7Gpio();                                            //开启 ePWM 对应 GPIO 时钟及初始化配置

    // 初始化时基模块，即配置 TB 相关寄存器值
    EPwm7Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // 时基周期立即加载模式
    EPwm7Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  时钟不同步

    // Allow each timer to be sync'ed
    EPwm7Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //使用相位同步功能
    EPwm7Regs.TBPHS.all = 0;                                    //相位寄存器清零
    EPwm7Regs.TBCTR = 0x0000;                                   // 清除计数器的值
    EPwm7Regs.TBPRD = tbprd;                                    // 周期频率
    EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // 为向上计数
    EPwm7Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm7Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // 时钟不分频

    // 初始化比较模块，即配置 CC 相关寄存器值
    EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // 加载方式为计数器为 0 加载
    EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // 影子寄存器

    // 设置比较器值
    EPwm7Regs.CMPA.bit.CMPA = tbprd/2;                          // Set compare A value 比较器值为 0

    // 初始化动作限定模块，即配置 AQ 相关寄存器值
    EPwm7Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm7Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm7Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //初始化事件触发模块，即配置 ET 相关寄存器值
    EPwm7Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;                  // ADCSOCA on TBCTR= zero
    EPwm7Regs.ETPS.bit.SOCAPRD = ET_1ST;                        // Generate SOCA on 1st event
    EPwm7Regs.ETSEL.bit.SOCAEN = 1;                             // Enable SOCA generation

    EPwm7Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm7Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm7Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm7Regs.DBRED.all = 0;                                    //Dead Band 0
    EPwm7Regs.DBFED.all = 0;
}

void EPWM8_Init()
{
    InitEPwm8Gpio();                                            //开启 ePWM 对应 GPIO 时钟及初始化配置

    // 初始化时基模块，即配置 TB 相关寄存器值
    EPwm8Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // 时基周期立即加载模式
    EPwm8Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  时钟不同步

    // Allow each timer to be sync'ed
    EPwm8Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //使用相位同步功能
    EPwm8Regs.TBPHS.all = 0;                                    //相位寄存器清零
    EPwm8Regs.TBCTR = 0x0000;                                   // 清除计数器的值
    EPwm8Regs.TBPRD = tbprd;                                    // 周期频率
    EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // 为向上计数
    EPwm8Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm8Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // 时钟不分频

    // 初始化比较模块，即配置 CC 相关寄存器值
    EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // 加载方式为计数器为 0 加载
    EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // 影子寄存器

    // 设置比较器值
    EPwm8Regs.CMPA.bit.CMPA = tbprd/2;                          // Set compare A value 比较器值为 0

    // 初始化动作限定模块，即配置 AQ 相关寄存器值
    EPwm8Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm8Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm8Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //初始化事件触发模块，即配置 ET 相关寄存器值
    EPwm8Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;                  // ADCSOCA on TBCTR= zero
    EPwm8Regs.ETPS.bit.SOCAPRD = ET_1ST;                        // Generate SOCA on 1st event
    EPwm8Regs.ETSEL.bit.SOCAEN = 1;                             // Enable SOCA generation

    EPwm8Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm8Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm8Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm8Regs.DBRED.all = 0;                                    //Dead Band 0
    EPwm8Regs.DBFED.all = 0;
}

void EPWM9_Init()
{

    InitEPwm9Gpio();                                            //开启 ePWM 对应 GPIO 时钟及初始化配置

    // 初始化时基模块，即配置 TB 相关寄存器值
    EPwm9Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // 时基周期立即加载模式
    EPwm9Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  时钟不同步

    // Allow each timer to be sync'ed
    EPwm9Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //使用相位同步功能
    EPwm9Regs.TBPHS.all = 0;                                    //相位寄存器清零
    EPwm9Regs.TBCTR = 0x0000;                                   // 清除计数器的值
    EPwm9Regs.TBPRD = tbprd;                                    // 周期频率
    EPwm9Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // 为向上计数
    EPwm9Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm9Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // 时钟不分频

    // 初始化比较模块，即配置 CC 相关寄存器值
    EPwm9Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // 加载方式为计数器为 0 加载
    EPwm9Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // 影子寄存器

    // 设置比较器值
    EPwm9Regs.CMPA.bit.CMPA = tbprd/2;                          // Set compare A value 比较器值为 0

    // 初始化动作限定模块，即配置 AQ 相关寄存器值
    EPwm9Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm9Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm9Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm9Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //初始化事件触发模块，即配置 ET 相关寄存器值
    EPwm9Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;                  // ADCSOCA on TBCTR= zero
    EPwm9Regs.ETPS.bit.SOCAPRD = ET_1ST;                        // Generate SOCA on 1st event
    EPwm9Regs.ETSEL.bit.SOCAEN = 1;                             // Enable SOCA generation

    EPwm9Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm9Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm9Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm9Regs.DBRED.all = 0;                                    //Dead Band 0
    EPwm9Regs.DBFED.all = 0;
}

void EPWM10_Init()
{
    InitEPwm10Gpio();                                           //开启 ePWM 对应 GPIO 时钟及初始化配置

    // 初始化时基模块，即配置 TB 相关寄存器值
    EPwm10Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                  // 时基周期立即加载模式
    EPwm10Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;            // Pass through  时钟不同步

    // Allow each timer to be sync'ed
    EPwm10Regs.TBCTL.bit.PHSEN = TB_DISABLE;                    //使用相位同步功能
    EPwm10Regs.TBPHS.all = 0;                                   //相位寄存器清零
    EPwm10Regs.TBCTR = 0x0000;                                  // 清除计数器的值
    EPwm10Regs.TBPRD = tbprd;                                   // 周期频率
    EPwm10Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                 // 为向上计数
    EPwm10Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm10Regs.TBCTL.bit.CLKDIV=TB_DIV1;                        // 时钟不分频

    // 初始化比较模块，即配置 CC 相关寄存器值
    EPwm10Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;              // 加载方式为计数器为 0 加载
    EPwm10Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                // 影子寄存器

    // 设置比较器值
    EPwm10Regs.CMPA.bit.CMPA = tbprd/2;                         // Set compare A value 比较器值为 0

    // 初始化动作限定模块，即配置 AQ 相关寄存器值
    EPwm10Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm10Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm10Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                       // Set PWM1B on Zero
    EPwm10Regs.AQCTLB.bit.CAU = AQ_SET;                         // Clear PWM1B on event B, up count

    //初始化事件触发模块，即配置 ET 相关寄存器值
    EPwm10Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;                 // ADCSOCA on TBCTR= zero
    EPwm10Regs.ETPS.bit.SOCAPRD = ET_1ST;                       // Generate SOCA on 1st event
    EPwm10Regs.ETSEL.bit.SOCAEN = 1;                            // Enable SOCA generation

    EPwm10Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm10Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm10Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm10Regs.DBRED.all = 0;                                   //Dead Band 0
    EPwm10Regs.DBFED.all = 0;
}

void EPWM11_Init()
{
    InitEPwm11Gpio();                                           //开启 ePWM 对应 GPIO 时钟及初始化配置

    // 初始化时基模块，即配置 TB 相关寄存器值
    EPwm11Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                  // 时基周期立即加载模式
    EPwm11Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;            // Pass through  时钟不同步

    // Allow each timer to be sync'ed
    EPwm11Regs.TBCTL.bit.PHSEN = TB_DISABLE;                    //使用相位同步功能
    EPwm11Regs.TBPHS.all = 0;                                   //相位寄存器清零
    EPwm11Regs.TBCTR = 0x0000;                                  // 清除计数器的值
    EPwm11Regs.TBPRD = tbprd;                                   // 周期频率
    EPwm11Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                 // 为向上计数
    EPwm11Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm11Regs.TBCTL.bit.CLKDIV=TB_DIV1;                        // 时钟不分频

    // 初始化比较模块，即配置 CC 相关寄存器值
    EPwm11Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;              // 加载方式为计数器为 0 加载
    EPwm11Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                // 影子寄存器

    // 设置比较器值
    EPwm11Regs.CMPA.bit.CMPA = tbprd/2;                         // Set compare A value 比较器值为 0

    // 初始化动作限定模块，即配置 AQ 相关寄存器值
    EPwm11Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm11Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm11Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                       // Set PWM1B on Zero
    EPwm11Regs.AQCTLB.bit.CAU = AQ_SET;                         // Clear PWM1B on event B, up count

    //初始化事件触发模块，即配置 ET 相关寄存器值
    EPwm11Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;                 // ADCSOCA on TBCTR= zero
    EPwm11Regs.ETPS.bit.SOCAPRD = ET_1ST;                       // Generate SOCA on 1st event
    EPwm11Regs.ETSEL.bit.SOCAEN = 1;                            // Enable SOCA generation

    EPwm11Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm11Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm11Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm11Regs.DBRED.all = 0;                                   //Dead Band 0
    EPwm11Regs.DBFED.all = 0;
}

void EPWM12_Init()
{
    InitEPwm12Gpio();                                           //开启 ePWM 对应 GPIO 时钟及初始化配置

    // 初始化时基模块，即配置 TB 相关寄存器值
    EPwm12Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                  // 时基周期立即加载模式
    EPwm12Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;            // Pass through  时钟不同步

    // Allow each timer to be sync'ed
    EPwm12Regs.TBCTL.bit.PHSEN = TB_DISABLE;                    //使用相位同步功能
    EPwm12Regs.TBPHS.all = 0;                                   //相位寄存器清零
    EPwm12Regs.TBCTR = 0x0000;                                  // 清除计数器的值
    EPwm12Regs.TBPRD = tbprd;                                   // 周期频率
    EPwm12Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                 // 为向上计数
    EPwm12Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm12Regs.TBCTL.bit.CLKDIV=TB_DIV1;                        // 时钟不分频

    // 初始化比较模块，即配置 CC 相关寄存器值
    EPwm12Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;              // 加载方式为计数器为 0 加载
    EPwm12Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                // 影子寄存器

    // 设置比较器值
    EPwm12Regs.CMPA.bit.CMPA = tbprd/2;                         // Set compare A value 比较器值为 0

    // 初始化动作限定模块，即配置 AQ 相关寄存器值
    EPwm12Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm12Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm12Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                       // Set PWM1B on Zero
    EPwm12Regs.AQCTLB.bit.CAU = AQ_SET;                         // Clear PWM1B on event B, up count

    //初始化事件触发模块，即配置 ET 相关寄存器值
    EPwm12Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;                 // ADCSOCA on TBCTR= zero
    EPwm12Regs.ETPS.bit.SOCAPRD = ET_1ST;                       // Generate SOCA on 1st event
    EPwm12Regs.ETSEL.bit.SOCAEN = 1;                            // Enable SOCA generation

    EPwm12Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm12Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm12Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm12Regs.DBRED.all = 0;                                   //Dead Band 0
    EPwm12Regs.DBFED.all = 0;
}
