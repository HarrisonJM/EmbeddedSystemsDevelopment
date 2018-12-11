/*!
 * @brief defines the main entry point for the program
 * @date 10/12/2018
 */

#include <msp430.h>

#include "helpers/boollint.h"

#include "buttons/buttonHandler.h"
#include "buttons/buttonHandlingUtility.h"
#include "hardwareAbstractions/public/I_button.h"

#include "hardwareAbstractions/public/I_led.h"

#include "hardwareAbstractions/public/I_lcd.h"
#include "screen/handler/screenHandler.h"

#include "menu/activities/ECG/activityECG.h"

#include "measurer/adc.h"

#include "timer/timer.h"

EVENTQUEUE_T* buttonS1Queue;
EVENTQUEUE_T* buttonS2Queue;

int main(void)
{
    /*! @todo move into an init function */
    /*!@{*/
    /*! @brief Stop watchdog timer */
    WDTCTL = WDTPW | WDTHOLD;
    /*!
     * @brief Disable the GPIO power-on default high-impedance mode
     * changing/removing this means that all pins must be set manually (including unused ones. Perhaps it helps with re-flashing?
     */
    PM5CTL0 &= ~LOCKLPM5;
    /*! @brief enable interrupts */
    _BIS_SR(GIE);
    /*!@}*/

    /* Setup button related things */
//    __ButtonHardwareinit();
//    ButtonInitHandlerBothButtons();
//    buttonS1Queue = ButtonGetQueue(BUTTONS1);
//    buttonS2Queue = ButtonGetQueue(BUTTONS2);

    /* Setup LED stuff*/
//    
    /* Timers and interrupts */
   // __LEDHardwareInit();

    bool invert = true; 
    /* Display stuff*/
    LCDInitHardware();
   // ScreenDisplayBufferInit(' ');
    ScreenPrintCustom(DisplayBuffer, "Hello World", invert);
    ScreenFlushDisplayBuffer();
    
    ///__TimerInit();
    
    //ADCInitHardware();
    //activityECGEnter();
    //activityECGTimer();
    /*char adcRdg [5];
    char timerAdcReading = 0;*/

    char adcRdg [5];
    char doneReading = 0;
    ADCStart();
    while(1)
    {
        
        if(timerAdcReading == 1)
        {
            if(doneReading == 0) 
            {
                //ScreenPrintCustom(DisplayBuffer, "Hello Worlsd", invert);
                //ScreenFlushDisplayBuffer();
                sprintf (adcRdg, "%d", rdg);
               ScreenPrintCustom(DisplayBuffer, adcRdg, invert);
                ScreenFlushDisplayBuffer();
                doneReading = 1;
            }
        }
        else
        {
            doneReading = 0;
        }
            
    }
/*


        if (adcReading == 1){
            if (doneReading == 0){
                /*setText (0, 24, "    ");
                sprintf (adcRdg, "%d", rdg);
                setText(0, 24, adcRdg);
                setText(40, 24,"bits");
                outputDisplayBuffer(0, 96);*/

               // doneReading = 1;
           // }

      /*  }else
            doneReading = 0;*/    

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
