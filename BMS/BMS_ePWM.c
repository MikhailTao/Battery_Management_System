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

    InitEPwm1Gpio();//���� ePWM ��Ӧ GPIO ʱ�Ӽ���ʼ������

    // ��ʼ��ʱ��ģ�飬������ TB ��ؼĴ���ֵ
    EPwm1Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // ʱ��������������ģʽ
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  ʱ�Ӳ�ͬ��

    // Allow each timer to be sync'ed
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //ʹ����λͬ������
    EPwm1Regs.TBPHS.all = 0;                                    //��λ�Ĵ�������
    EPwm1Regs.TBCTR = 0x0000;                                   // �����������ֵ
    EPwm1Regs.TBPRD = tbprd;                                    // ����Ƶ��
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // Ϊ���ϼ���
    EPwm1Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // ʱ�Ӳ���Ƶ

    // ��ʼ���Ƚ�ģ�飬������ CC ��ؼĴ���ֵ
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // ���ط�ʽΪ������Ϊ 0 ����
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // Ӱ�ӼĴ���

    // ���ñȽ���ֵ
    EPwm1Regs.CMPA.bit.CMPA = 0;                                // Set Duty Ratio to 0 at beginning

    // ��ʼ�������޶�ģ�飬������ AQ ��ؼĴ���ֵ
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm1Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm1Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //��ʼ���¼�����ģ�飬������ ET ��ؼĴ���ֵ
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

    InitEPwm2Gpio();                                            //���� ePWM ��Ӧ GPIO ʱ�Ӽ���ʼ������

    // ��ʼ��ʱ��ģ�飬������ TB ��ؼĴ���ֵ
    EPwm2Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // ʱ��������������ģʽ
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  ʱ�Ӳ�ͬ��

    // Allow each timer to be sync'ed
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //ʹ����λͬ������
    EPwm2Regs.TBPHS.all = 0;                                    //��λ�Ĵ�������
    EPwm2Regs.TBCTR = 0x0000;                                   // �����������ֵ
    EPwm2Regs.TBPRD = tbprd;                                    // ����Ƶ��
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // Ϊ���ϼ���
    EPwm2Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm2Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // ʱ�Ӳ���Ƶ

    // ��ʼ���Ƚ�ģ�飬������ CC ��ؼĴ���ֵ
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // ���ط�ʽΪ������Ϊ 0 ����
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // Ӱ�ӼĴ���

    // ���ñȽ���ֵ
    EPwm2Regs.CMPA.bit.CMPA = tbprd/2;                          // Set compare A value �Ƚ���ֵΪ 0

    // ��ʼ�������޶�ģ�飬������ AQ ��ؼĴ���ֵ
    EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm2Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm2Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //��ʼ���¼�����ģ�飬������ ET ��ؼĴ���ֵ
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

    InitEPwm3Gpio();//���� ePWM ��Ӧ GPIO ʱ�Ӽ���ʼ������

    // ��ʼ��ʱ��ģ�飬������ TB ��ؼĴ���ֵ
    EPwm3Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // ʱ��������������ģʽ
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  ʱ�Ӳ�ͬ��

    // Allow each timer to be sync'ed
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //ʹ����λͬ������
    EPwm3Regs.TBPHS.all = 0;                                    //��λ�Ĵ�������
    EPwm3Regs.TBCTR = 0x0000;                                   // �����������ֵ
    EPwm3Regs.TBPRD = tbprd;                                    // ����Ƶ��
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // Ϊ���ϼ���
    EPwm3Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm3Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // ʱ�Ӳ���Ƶ

    // ��ʼ���Ƚ�ģ�飬������ CC ��ؼĴ���ֵ
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // ���ط�ʽΪ������Ϊ 0 ����
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // Ӱ�ӼĴ���

    // ���ñȽ���ֵ
    EPwm3Regs.CMPA.bit.CMPA = 0;                                // Set Duty Ratio to 0 at beginning

    // ��ʼ�������޶�ģ�飬������ AQ ��ؼĴ���ֵ
    EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm3Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm3Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //��ʼ���¼�����ģ�飬������ ET ��ؼĴ���ֵ
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

    InitEPwm4Gpio();                                            //���� ePWM ��Ӧ GPIO ʱ�Ӽ���ʼ������

    // ��ʼ��ʱ��ģ�飬������ TB ��ؼĴ���ֵ
    EPwm4Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;                   // ʱ��������������ģʽ
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;             // Pass through  ʱ�Ӳ�ͬ��

    // Allow each timer to be sync'ed
    EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;                     //ʹ����λͬ������
    EPwm4Regs.TBPHS.all = 0;                                    //��λ�Ĵ�������
    EPwm4Regs.TBCTR = 0x0000;                                   // �����������ֵ
    EPwm4Regs.TBPRD = tbprd;                                    // ����Ƶ��
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;                  // Ϊ���ϼ���
    EPwm4Regs.TBCTL.bit.HSPCLKDIV= TB_DIV1;
    EPwm4Regs.TBCTL.bit.CLKDIV=TB_DIV1;                         // ʱ�Ӳ���Ƶ

    // ��ʼ���Ƚ�ģ�飬������ CC ��ؼĴ���ֵ
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;               // ���ط�ʽΪ������Ϊ 0 ����
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;                 // Ӱ�ӼĴ���

    // ���ñȽ���ֵ
    EPwm4Regs.CMPA.bit.CMPA = tbprd/2;                          // Set compare A value �Ƚ���ֵΪ 0

    // ��ʼ�������޶�ģ�飬������ AQ ��ؼĴ���ֵ
    EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm4Regs.AQCTLB.bit.ZRO = AQ_CLEAR;                        // Set PWM1B on Zero
    EPwm4Regs.AQCTLB.bit.CAU = AQ_SET;                          // Clear PWM1B on event B, up count

    //��ʼ���¼�����ģ�飬������ ET ��ؼĴ���ֵ
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
