/*!
 * @brief Implements the timer interrupts
 * @author Harrison Marcks
 * @date 10/12/18
 * @addtogroup interrupt
 * @{
 */
#include <helpers/eventQueue/eventQueue.h>
#include <msp430fr5969.h>

#include "buttons/buttonHandler.h"
#include "buttons/buttonHandlingUtility.h"
#include "leds/LedHandler.h"
#include "hardwareAbstractions/public/I_led.h"

/*#include "menu/activities/ECG/activityECG.h"*/
#include "menu/activities/activites.h"

extern volatile int timerAdcReading;
/* Counter */
static int msCounter10 = 0;
static int msCounter100 = 0;
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
    if(msCounter10 == 10)
    {
        EVENTQUEUE_T* S1QUEUE = ButtonGetQueue(BUTTONS2);
        if(S1QUEUE->size > 0)
            LEDUse(LED_RED, LED_TOGGLE);
        msCounter10 = 0;
    }
}
/*
///*
// * @brief This ISR clears the LPM bits found in the Status Register (SR/R2)
// * used when performing capacitive touch checks
// */
//#pragma vector=TIMER3_A0_VECTOR
//__interrupt void TIMER3_A0_ISR(void)
//{
//    __bic_SR_register_on_exit(LPM3_bits);           // Exit LPM3 on reti
//} */

/*! @} */
