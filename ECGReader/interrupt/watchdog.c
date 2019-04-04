/*!
 * @brief the watchdog timer interrupt service routine
 * @author Harrison Marcks
 * @date 10/12/18
 * @addtogroup interrupt
 * @{
 */

#include <msp430.h>
#include "helpers/boollint.h"
#include "hardwareAbstractions/public/I_led.h"

#include "leds/LedHandler.h"

extern volatile bool restarting;

extern int main();

/*  Watchdog interrupt service */
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    WDTCTL = WDTPW + WDTCNTCL + 3; /* Reset the watchdog */
    restarting = true;
    LEDUse(LED_GREEN
           , LED_TOGGLE);
    /* main(); */
}

/*! @} */
