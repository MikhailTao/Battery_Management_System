/*
 * BMS_LED.c
 *
 *  Created on: 2024-01-19
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: LED source file
 */

#include "F2837xD_device.h"                                     // F2837xD Header file Include File
#include "F2837xD_Examples.h"                                   // F2837xD Examples Include File
#include "BMS_LED.h"

void Init_LED (void){
    LED_GPIO();

    //
    // Set all LED pins to LOW
    //

    // EM1D0
    GpioDataRegs.GPCCLEAR.bit.GPIO85 = 1;
    // EM1D1
    GpioDataRegs.GPCCLEAR.bit.GPIO83 = 1;
    // EM1D2
    GpioDataRegs.GPCCLEAR.bit.GPIO82 = 1;
    // EM1D3
    GpioDataRegs.GPCCLEAR.bit.GPIO81 = 1;
    // EM1D4
    GpioDataRegs.GPCCLEAR.bit.GPIO80 = 1;
    // EM1D5
    GpioDataRegs.GPCCLEAR.bit.GPIO79 = 1;
    // EM1D6
    GpioDataRegs.GPCCLEAR.bit.GPIO78 = 1;
    // EM1D7
    GpioDataRegs.GPCCLEAR.bit.GPIO77 = 1;
    // EM1D8
    GpioDataRegs.GPCCLEAR.bit.GPIO76 = 1;
    // EM1D9
    GpioDataRegs.GPCCLEAR.bit.GPIO75 = 1;
    // EM1D10
    GpioDataRegs.GPCCLEAR.bit.GPIO74 = 1;
    // EM1D11
    GpioDataRegs.GPCCLEAR.bit.GPIO73 = 1;
    // EM1D12
    GpioDataRegs.GPCCLEAR.bit.GPIO72 = 1;
    // EM1D13
    GpioDataRegs.GPCCLEAR.bit.GPIO71 = 1;
    // EM1D14
    GpioDataRegs.GPCCLEAR.bit.GPIO70 = 1;
    // EM1D15
    GpioDataRegs.GPCCLEAR.bit.GPIO69 = 1;

    // EM1BA0
    GpioDataRegs.GPCCLEAR.bit.GPIO93 = 1;
    // EM1BA1
    GpioDataRegs.GPCCLEAR.bit.GPIO92 = 1;

    // EM1A0
    GpioDataRegs.GPBCLEAR.bit.GPIO38 = 1;
    // EM1A1
    GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;
    // EM1A2
    GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1;
    // EM1A3
    GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;
    // EM1A4
    GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
    // EM1A5
    GpioDataRegs.GPBCLEAR.bit.GPIO45 = 1;
    // EM1A6
    GpioDataRegs.GPBCLEAR.bit.GPIO46 = 1;
    // EM1A7
    GpioDataRegs.GPBCLEAR.bit.GPIO47 = 1;
    // EM1A8
    GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1;
    // EM1A9
    GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;
}

void LED_GPIO (void){
    // EM1D0
    GPIO_SetupPinMux(85, GPIO_MUX_CPU1, 0);                     //Pin   85      CPU1    option 0
    GPIO_SetupPinOptions(85, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  85      Output  PushPull
    // EM1D1
    GPIO_SetupPinMux(83, GPIO_MUX_CPU1, 0);                     //Pin   83      CPU1    option 0
    GPIO_SetupPinOptions(83, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  83      Output  PushPull
    // EM1D2
    GPIO_SetupPinMux(82, GPIO_MUX_CPU1, 0);                     //Pin   82      CPU1    option 0
    GPIO_SetupPinOptions(82, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  82      Output  PushPull
    // EM1D3
    GPIO_SetupPinMux(81, GPIO_MUX_CPU1, 0);                     //Pin   81      CPU1    option 0
    GPIO_SetupPinOptions(81, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  81      Output  PushPull
    // EM1D4
    GPIO_SetupPinMux(80, GPIO_MUX_CPU1, 0);                     //Pin   80      CPU1    option 0
    GPIO_SetupPinOptions(80, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  80      Output  PushPull
    // EM1D5
    GPIO_SetupPinMux(79, GPIO_MUX_CPU1, 0);                     //Pin   79      CPU1    option 0
    GPIO_SetupPinOptions(79, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  79      Output  PushPull
    // EM1D6
    GPIO_SetupPinMux(78, GPIO_MUX_CPU1, 0);                     //Pin   78      CPU1    option 0
    GPIO_SetupPinOptions(78, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  78      Output  PushPull
    // EM1D7
    GPIO_SetupPinMux(77, GPIO_MUX_CPU1, 0);                     //Pin   77      CPU1    option 0
    GPIO_SetupPinOptions(77, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  77      Output  PushPull
    // EM1D8
    GPIO_SetupPinMux(76, GPIO_MUX_CPU1, 0);                     //Pin   76      CPU1    option 0
    GPIO_SetupPinOptions(76, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  76      Output  PushPull
    // EM1D9
    GPIO_SetupPinMux(75, GPIO_MUX_CPU1, 0);                     //Pin   75      CPU1    option 0
    GPIO_SetupPinOptions(75, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  75      Output  PushPull
    // EM1D10
    GPIO_SetupPinMux(74, GPIO_MUX_CPU1, 0);                     //Pin   74      CPU1    option 0
    GPIO_SetupPinOptions(74, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  74      Output  PushPull
    // EM1D11
    GPIO_SetupPinMux(73, GPIO_MUX_CPU1, 0);                     //Pin   73      CPU1    option 0
    GPIO_SetupPinOptions(73, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  73      Output  PushPull
    // EM1D12
    GPIO_SetupPinMux(72, GPIO_MUX_CPU1, 0);                     //Pin   72      CPU1    option 0
    GPIO_SetupPinOptions(72, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  72      Output  PushPull
    // EM1D13
    GPIO_SetupPinMux(71, GPIO_MUX_CPU1, 0);                     //Pin   71      CPU1    option 0
    GPIO_SetupPinOptions(71, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  71      Output  PushPull
    // EM1D14
    GPIO_SetupPinMux(70, GPIO_MUX_CPU1, 0);                     //Pin   70      CPU1    option 0
    GPIO_SetupPinOptions(70, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  70      Output  PushPull
    // EM1D15
    GPIO_SetupPinMux(69, GPIO_MUX_CPU1, 0);                     //Pin   69      CPU1    option 0
    GPIO_SetupPinOptions(69, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  69      Output  PushPull

    // EM1BA0
    GPIO_SetupPinMux(93, GPIO_MUX_CPU1, 0);                     //Pin   93      CPU1    option 0
    GPIO_SetupPinOptions(93, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  93      Output  PushPull
    // EM1BA1
    GPIO_SetupPinMux(92, GPIO_MUX_CPU1, 0);                     //Pin   92      CPU1    option 0
    GPIO_SetupPinOptions(92, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  92      Output  PushPull

    // EM1A0
    GPIO_SetupPinMux(38, GPIO_MUX_CPU1, 0);                     //Pin   38      CPU1    option 0
    GPIO_SetupPinOptions(38, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  38      Output  PushPull
    // EM1A1
    GPIO_SetupPinMux(39, GPIO_MUX_CPU1, 0);                     //Pin   39      CPU1    option 0
    GPIO_SetupPinOptions(39, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  39      Output  PushPull
    // EM1A2
    GPIO_SetupPinMux(40, GPIO_MUX_CPU1, 0);                     //Pin   40      CPU1    option 0
    GPIO_SetupPinOptions(40, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  40      Output  PushPull
    // EM1A3
    GPIO_SetupPinMux(41, GPIO_MUX_CPU1, 0);                     //Pin   41      CPU1    option 0
    GPIO_SetupPinOptions(41, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  41      Output  PushPull
    // EM1A4
    GPIO_SetupPinMux(44, GPIO_MUX_CPU1, 0);                     //Pin   44      CPU1    option 0
    GPIO_SetupPinOptions(44, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  44      Output  PushPull
    // EM1A5
    GPIO_SetupPinMux(45, GPIO_MUX_CPU1, 0);                     //Pin   45      CPU1    option 0
    GPIO_SetupPinOptions(45, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  45      Output  PushPull
    // EM1A6
    GPIO_SetupPinMux(46, GPIO_MUX_CPU1, 0);                     //Pin   46      CPU1    option 0
    GPIO_SetupPinOptions(46, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  46      Output  PushPull
    // EM1A7
    GPIO_SetupPinMux(47, GPIO_MUX_CPU1, 0);                     //Pin   47      CPU1    option 0
    GPIO_SetupPinOptions(47, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  47      Output  PushPull
    // EM1A8
    GPIO_SetupPinMux(48, GPIO_MUX_CPU1, 0);                     //Pin   48      CPU1    option 0
    GPIO_SetupPinOptions(48, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  48      Output  PushPull
    // EM1A9
    GPIO_SetupPinMux(49, GPIO_MUX_CPU1, 0);                     //Pin   49      CPU1    option 0
    GPIO_SetupPinOptions(49, GPIO_OUTPUT, GPIO_PUSHPULL);       //GPIO  49      Output  PushPull
}
