/*!
 * @brief Hardware implementations for using the LEDs
 * @author Harrison Marcks
 * @addtogroup hardwareAbstractions
 * @addtogroup ledPrivate
 * @date 12/11/18
 */

#include <msp430.h>
#include "../public/I_led.h"
/*!
 * @brief Inits the LED hardware
 */
void __LEDHardwareInit(void)
{
    P1DIR |= BIT0; /* green, P1.0, 0b0000 0001 */
    P4DIR |= BIT2; /* red,   P4.6, 0b0100 0000*/
    __LEDGreenOff();
    __LEDRedOff();
}
/*!
 * @brief Toggles the red LED
 */
void __LEDRedToggle(void)
{
    P4OUT ^= BIT2;
}
/*!
 * Turns off the red LED
 */
void __LEDRedOff(void)
{
    P4OUT &= (0xFF-BIT2);
}
/*!
 * Turns on the red LED
 */
void __LEDRedOn(void)
{
    P4OUT |= BIT2;
}
/*!
 * @brief Toggles the green LED
 */
void __LEDGreenToggle(void)
{
    P1OUT ^= BIT0;
}
/*!
 * @brief Turns off the green LED
 */
void __LEDGreenOff(void)
{
    P1OUT &= (0xFF-BIT0);
}
/*!
 * @brief Turns on the green LED
 */
void __LEDGreenOn(void)
{
    P1OUT |= BIT0;
}

