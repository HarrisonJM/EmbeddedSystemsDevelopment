/*!
 * @brief defines the main entry point for the program
 * @date 10/12/2018
 */

#include <msp430.h>

#include "postPowerOn/POST.h"

#include "helpers/eventQueue/eventQueue.h"

#include "menu/activities/activites.h"

#include "leds/LedHandler.h"
#include "leds/LedHandlerUtility.h"

EVENTQUEUE_T* buttonS1Queue;
EVENTQUEUE_T* buttonS2Queue;

int main(void)
{
    /* Perform the post */
    POST();

    //ActivityECGEnter();

//    ScreenPrint("TEST", false);
//    ScreenSetText(0, 0, "TEST", false);
    ScreenPrint("Post success...", 1);
    ScreenFlushDisplayBuffer();
    while(1)
    {
        //ActivityECGTimer();
        
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
