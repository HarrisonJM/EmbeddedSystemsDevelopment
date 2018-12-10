/*!
 * @brief Hardware implementations for using the LEDs
 * @author Harrison Marcks
 * @date 12/11/18
 */

#include <msp430.h>

/* Prototypes */
void __LEDRedOff();
void __LEDGreenOff();

/*!
 * @brief Inits the LED hardware
 */
void __LEDHardwareInit()
{
    P1DIR |= BIT0; /* green, P1.0, 0b0000 0001 */
    P4DIR |= BIT2; /* red,   P4.6, 0b0100 0000*/
    __LEDGreenOff();
    __LEDRedOff();
}
/*!
 * @brief Toggles the red LED
 */
void __LEDRedToggle()
{
    P4OUT ^= BIT2;
}
/*!
 * Turns off the red LED
 */
void __LEDRedOff()
{
    P4OUT &= (0xFF-BIT2);
}
/*!
 * Turns on the red LED
 */
void __LEDRedOn()
{
    P4OUT |= BIT2;
}
/*!
 * @brief Toggles the green LED
 */
void __LEDGreenToggle()
{
    P1OUT ^= BIT0;
}
/*!
 * @brief Turns off the green LED
 */
void __LEDGreenOff()
{
    P1OUT &= (0xFF-BIT0);
}
/*!
 * @brief Turns on the green LED
 */
void __LEDGreenOn()
{
    P1OUT |= BIT0;
}
