/*!
 * @brief functions for controlling the watchdog Timer
 * @author Harrison Marcks
 * @date 10/12/2018
 */

#include <msp430.h>

/*!
 * @brief Holds/stops the watchdog timer
 */
void WatchdogStop(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
}
/*!
 * @brief starts/re-enables the watchdog timer
 */
void WatchDogEnable(void)
{
    WDTCTL = WDTPW + WDTCNTCL + 3;  /* Enable the Watchdog Timer */
}
