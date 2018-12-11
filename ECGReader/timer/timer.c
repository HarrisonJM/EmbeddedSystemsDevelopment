/*!
 * @brief implements the 1ms timer interrupt
 *
 *  Created on: 17 Nov 2015
 *      Author: Len Biro
 */
#include <msp430.h>

#include "buttons/buttonHandler.h"
#include "buttons/buttonHandlingUtility.h"
//#include "leds/LedHandler.h"
//#include "leds/LedHandlerUtility.h"
#include "eventQueue/eventQueue.h"
#include "hardwareAbstractions/public/I_led.h"

/* Counter */
int msCounter10 = 0;
int msCounter100 = 0;
int timerAdcReading = 1;

/* Queues */
extern EVENTQUEUE_T* buttonS1Queue;
extern EVENTQUEUE_T* buttonS2Queue;

/*!
 * @brief Inits Timer0(1ms)
 */
void __TimerInit(void)
{
    TA0CCR0 = 1024; /* Count up to 1024 */
    TA0CCTL0 = 0x10; /* Enable counter interrupts, bit 4=1 (5th bit = 1) */

    TA0CCTL1 = OUTMOD_3;                        // TACCR1 set/reset
    TA0CCR1 = 1023;                             // TACCR1 PWM Duty Cycle
    TA0CTL = TASSEL_2 + MC_1; // Timer A using subsystem master clock, SMCLK(1.1 MHz)
                              // and count UP to create a 1ms interrupt
                              // PWM Period
}
/*!
 * @brief Timer0 A0 1ms interrupt service routine
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
    msCounter10++;
    msCounter100++;

    if (10 == msCounter10)
    {
//        ButtonTimer(BUTTONS1);
//        ButtonTimer(BUTTONS2);
    }

    timerAdcReading++;
    if(timerAdcReading >= 40)
    {
        timerAdcReading = 1;
    }

    if(ButtonGetState(BUTTONS2) == EVENT_BUTTON_PRESSED)
        __LEDGreenOn();

    if(buttonS1Queue->size > 0)
    {
        /*!
         * @todo here we would actually pop from the
         * queue into an event and use that for everything
         * that requires it
         */
        EVENT_T e;
        buttonS1Queue->PopFront(buttonS1Queue, &e);

        if(e.event == EVENT_BUTTON_PRESSED)
        {
            __LEDRedOn();
        }
        else
        {
            __LEDRedOff();
        }
    }
}
