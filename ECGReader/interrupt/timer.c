/*!
 * @brief Implements the timer interrupts
 * @author Harrison Marcks
 * @date 10/12/18
 */
#include <helpers/eventQueue/eventQueue.h>
#include <msp430.h>

#include "buttons/buttonHandler.h"
#include "buttons/buttonHandlingUtility.h"
//#include "leds/LedHandler.h"
//#include "leds/LedHandlerUtility.h"
#include "hardwareAbstractions/public/I_led.h"


extern volatile int timerAdcReading;
/* Counter */
int msCounter10 = 0;
int msCounter100 = 0;
/* Queues */
extern EVENTQUEUE_T* buttonS1Queue;
extern EVENTQUEUE_T* buttonS2Queue;

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

//    if(ButtonGetState(BUTTONS2) == EVENT_BUTTON_PRESSED)
//        __LEDGreenOn();
//
//    if(buttonS1Queue->size > 0)
//    {
//        /*!
//         * @todo here we would actually pop from the
//         * queue into an event and use that for everything
//         * that requires it
//         */
//        EVENT_T e;
//        buttonS1Queue->PopFront(buttonS1Queue, &e);
//
//        if(e.event == EVENT_BUTTON_PRESSED)
//        {
//            __LEDRedOn();
//        }
//        else
//        {
//            __LEDRedOff();
//        }
//    }
}
