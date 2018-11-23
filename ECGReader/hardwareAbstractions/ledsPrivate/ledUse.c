/*!
 * @brief Hardware implementations for using the LEDs
 * @author Harrison Marcks
 * @date 12/11/18
 */

#include <msp430.h>

/*!
 * @brief Inits the LED hardware
 */
void __LEDHardwareInit()
{
    P1DIR |= 0x01; /* green, P1.0, 0b0000 0001 */
    P4DIR |= 0x40; /* red,   P4.6, 0b0100 0000*/
}
/*!
 * @brief Toggles the red LED
 */
void __LEDRedToggle()
{
    P4OUT ^= 0x40;
}
/*!
 * Turns off the red LED
 */
void __LEDRedOff()
{
    P4OUT &= (0xFF-0x40);
}
/*!
 * Turns on the red LED
 */
void __LEDRedOn()
{
    P4OUT |= 0x40;
}
/*!
 * @brief Toggles the green LED
 */
void __LEDGreenToggle()
{
    P1OUT ^= 0x01;
}
/*!
 * @brief Turns off the green LED
 */
void __LEDGreenOff()
{
    P1OUT &= (0xFF-0x01);
}
/*!
 * @brief Turns on the green LED
 */
void __LEDGreenOn()
{
    P1OUT |= 0x01;
}
