/*!
 * @brief defines the main entry point for the program
 * @author Jesse Batt
 * @date 10/12/2018
 * @todo TIDY EVERYTHING
 */

#include <msp430.h>
#include "helpers/boollint.h"
#include "postPowerOn/POST.h"

#include "hardwareAbstractions/public/I_led.h"
#include "hardwareAbstractions/public/I_button.h"
#include "hardwareAbstractions/public/I_lcd.h"
#include "hardwareAbstractions/public/I_sliders.h"
#include "hardwareAbstractions/public/I_watchdog.h"
#include "hardwareAbstractions/public/I_interrupt.h"

#include "buttons/buttonHandlingUtility.h"
#include "buttons/buttonHandler.h"

#include "screen/handler/screenHandler.h"

/* Variable */
volatile bool restarting = false;

void RAMCheck1()
{
    asm(
         "      mov.w #001C00h, R12 \n"
         "loop1: \n"
         "      mov.w #00000h, 0(R12) \n"
         "      cmp.w #00000h, 0(R12) \n"
         "      jne loop1 \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop1 \n"
        );

    __LEDGreenOn();
    __LEDRedOff();
}

void RAMCheck2()
{
    asm(
         "      mov.w #001C00h, R12 \n"
         "loop2: \n"
         "      mov.w #0ffffh, 0(R12) \n"
         "      cmp.w #0ffffh, 0(R12) \n"
         "      jne loop2 \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop2 \n"
        );

    __LEDGreenOff();
    __LEDRedOn();
}

void RAMCheck3()
{
    asm(
         "      mov.w #001C00h, R12 \n"
         "loop3: \n"
         "      mov.w #05555h, 0(R12) \n"
         "      cmp.w #05555h, 0(R12) \n"
         "      jne loop3 \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop3 \n"
        );

    __LEDGreenOn();
    __LEDRedOff();
}

void RAMCheck4()
{
    asm(
         "      mov.w #001C00h, R12 \n"
         "loop4: \n"
         "      mov.w #0aaaah, 0(R12) \n"
         "      cmp.w #0aaaah, 0(R12) \n"
         "      jne loop4 \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop4 \n"
        );

    __LEDGreenOff();
    __LEDRedOn();
}

void RAMCheck5()
{
    asm(
         "      mov.w #001C00h, R12 \n"
         "loop5: \n"
         "      mov.w R12, 0(R12) \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop5 \n"
        );

    __LEDGreenOn();
    __LEDRedOff();
}

void RAMCheck6()
{
    asm(
        "      mov.w #001C00h, R12 \n"
        "loop6: \n"
        "      cmp.w R12, 0(R12) \n"
        "      jne loop6 \n"
        "      add #2, R12 \n"
        "      cmp.w #002400h, R12 \n"
        "      jn loop6 \n"
        );

    __LEDGreenOff();
    __LEDRedOn();
}

void RAMCheck7()
{
    asm(
         "      mov.w #001C00h, R12 \n"
         "loop7: \n"
         "      mov.w #00000h, 0(R12) \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop7 \n"
        );

    __LEDGreenOn();
    __LEDRedOff();
}

/*
 * @brief performs the POST. Also handles hardware and software initialization
 */
void POST(void)
{
    WatchdogStop();

    /*!
     * @brief Disable the GPIO power-on default high-impedance mode
     * to activate previously configured port settings
     */
    PM5CTL0 &= ~LOCKLPM5;

    /* Check restart  for re-init */
    if (restarting == true)
    {
        goto restart_here;
    }

    /* LEDs need init'ing before RAM check for the lights in each RAM check */
    __LEDHardwareInit();

    /* RAM Checks */
    RAMCheck1();
    RAMCheck2();
    RAMCheck3();
    RAMCheck4();
    RAMCheck5();
    RAMCheck6();
    RAMCheck7();

    /* Initialisations */
    __ButtonHardwareinit();

    /* Timers */
    InterruptTimerA0Init();
    InterruptTimerA2Init();

    /* Sliders */
    SliderHardwareInit();

    /* Screen Hardware */
    LCDInitHardware();

    __LEDGreenOff();
    __LEDRedOn();

    /* Initialisation - Software */
    ButtonHandlerInitBothButtons();
    /* Clear the Screen */
    ScreenDisplayBufferInit(' ');
    ScreenFlushDisplayBuffer();

    InterruptEnable();

restart_here:

    WatchDogEnable();

    /* Re-set the stack pointer */

    asm(
         "      mov.w #002400h, SP \n"
        );
}
