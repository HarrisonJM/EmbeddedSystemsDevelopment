/*
 * main.c
 */

#include <msp430.h>
#include <stdio.h>
#include <string.h>

#include "buttons/buttonHandler.h"
#include "buttons/buttonHandlingUtility.h"
#include "leds/LedHandler.h"
#include "leds/LedHandlerUtility.h"
#include "hardwareAbstractions/I_button.h"
#include "hardwareAbstractions/I_led.h"
#include "timer/timer.h"

#include "buttons/private/O_button.h"

EVENTQUEUE_T* buttonS1Queue;
EVENTQUEUE_T* buttonS2Queue;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode
    _BIS_SR(GIE); // enable interrupts

    /* Setup button related things */
    __ButtonHardwareinit();
    ButtonInitHandlerBothButtons();
    buttonS1Queue = ButtonGetQueue(BUTTONS1);
    buttonS2Queue = ButtonGetQueue(BUTTONS2);

    __LEDHardwareInit();
    LEDInitHandlerBothLEDs();
    __TimerInit();

    while(1)
    {
        BUTTONSTATE_E state = ButtonGetState(BUTTONS1);

        if (__ReadButtonS1() == false)
        {
            __LEDGreenOn();
        }
        else
        {
            __LEDGreenOff();
        }

//        state = ButtonGetState(BUTTONS2);
//
//        if ((state == BUTTON_PRESSED))
//        {
//            __LEDRedOn();
//        }
//        else
//        {
//            __LEDRedOff();
//        }
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
