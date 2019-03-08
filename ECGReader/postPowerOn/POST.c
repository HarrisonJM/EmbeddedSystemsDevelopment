/*!
 * @brief POST, RAM Checks, some initialisation
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

#include "buttons/buttonHandler.h"
#include "leds/LedHandler.h"

#include "screen/handler/screenHandler.h"

/* Variable */
volatile bool restarting = false;

void RAMCheck1(void)
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
}

void RAMCheck2(void)
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
}

void RAMCheck3(void)
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
}

void RAMCheck4(void)
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
}

void RAMCheck5(void)
{
    asm(
         "      mov.w #001C00h, R12 \n"
         "loop5: \n"
         "      mov.w R12, 0(R12) \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop5 \n"
        );
}

void RAMCheck6(void)
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
}

void RAMCheck7(void)
{
    asm(
         "      mov.w #001C00h, R12 \n"
         "loop7: \n"
         "      mov.w #00000h, 0(R12) \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop7 \n"
        );
}
/*
 * @brief Resets the stack pointer
 */
void ResetStackPoint(void)
{
    asm(
         "      mov.w #002400h, SP \n"
        );
}
void ToggleLEDs(void)
{
    LEDUse(LED_GREEN, LED_TOGGLE);
    LEDUse(LED_RED, LED_TOGGLE);
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

    /*! @todo Figure out how to deal with watchdog goto restarting thing */
//    if(true == restarting)
//    {
//        goto labelRestart;
//    }

    /* LEDs need init'ing before RAM check for the lights in each RAM check */
    __LEDHardwareInit();
    LEDHandlerInitBothLEDs();

//    /* RAM Checks */
//    RAMCheck1();
//    LEDUse(LED_GREEN, LED_ON);
//    LEDUse(LED_RED, LED_OFF);
//    RAMCheck2();
//    ToggleLEDs();
//    RAMCheck3();
//    ToggleLEDs();
//    RAMCheck4();
//    ToggleLEDs();
//    RAMCheck5();
//    ToggleLEDs();
//    RAMCheck6();
//    ToggleLEDs();
//    RAMCheck7();
//    ToggleLEDs();

    /* Initialisations */
    __ButtonHardwareinit();

    /* Timers */
    InterruptTimerA0Init();
    InterruptTimerA2Init();

    /* Sliders */
    SliderHardwareInit();

    /* Screen Hardware */
    LCDInitHardware();

//    ToggleLEDs();

    /* Initialisation - Software */
    ButtonHandlerInitBothButtons();

    /* Clear the Screen */
    ScreenDisplayBufferInit("");
    ScreenFlushDisplayBuffer();

    InterruptEnable();

    /*! @todo Figure out how to deal with watchdog goto restarting thing */
//labelRestart:

//    WatchDogEnable();

//    ResetStackPoint();
}
