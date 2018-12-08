/*
 * main.c
 */

#include <msp430.h>
#include <screen/handler/screenHandler.h>

#include "helpers/boollint.h"

#include "buttons/buttonHandler.h"
#include "buttons/buttonHandlingUtility.h"
#include "buttons/private/O_button.h"
#include "hardwareAbstractions/public/I_button.h"

#include "leds/LedHandler.h"
#include "leds/LedHandlerUtility.h"
#include "hardwareAbstractions/public/I_led.h"

#include "timer/timer.h"

#include "hardwareAbstractions/public/I_lcd.h"

EVENTQUEUE_T* buttonS1Queue;
EVENTQUEUE_T* buttonS2Queue;

int main(void)
{
    /*! @brief Stop watchdog timer */
    WDTCTL = WDTPW | WDTHOLD;
    /*!
     * @brief Disable the GPIO power-on default high-impedance mode
     * Changining/removing this means that all pins must be set manually (including unused ones. Perhaps it helps with re-flashing?
     */
    PM5CTL0 &= ~LOCKLPM5;
    /*! @brief enable interrupts */
    _BIS_SR(GIE);

    /* Setup button related things */
    __ButtonHardwareinit();
    ButtonInitHandlerBothButtons();
    buttonS1Queue = ButtonGetQueue(BUTTONS1);
    buttonS2Queue = ButtonGetQueue(BUTTONS2);

    /* Setup LED stuff*/
    __LEDHardwareInit();
    /* Timers and interrupts */
    __TimerInit();

    /* Display stuff*/
    LCDInitHardware();
    ScreenDisplayBufferInit(' ');
    ScreenFlushDisplayBuffer();

    ScreenPrint("Hello, World!",
                false);
    ScreenFlushDisplayBuffer();

    while(1)
    {
    }

//    char adcRdg [5];
//    char doneReading = 0;
//
//    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
//    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode
//
//    initTimer();
//    initDisplay();
//    outputDisplayBuffer(0, 96);
//    _BIS_SR (GIE);
//
//    setText(0, 1, "A-D chnl 12 ");
//    outputDisplayBuffer(0,96);
//    adc_1();
//    while (1)
//    {
//        if (timerAdcReading == 1)
//        {
//            if (doneReading == 0)
//            {
//                setText (0, 24, "    ");
//                sprintf (adcRdg, "%d", rdg);
//                setText(0, 24, adcRdg);
//                setText(40, 24,"bits");
//                outputDisplayBuffer(0, 96);
//                doneReading = 1;
//            }
//
//        }
//        else
//        {
//            doneReading = 0;
//        }
//
//    }

//    return 0;
}
