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
    P1DIR |= 0X01; /* green */
    P4DIR |= 0x20; /* red */
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
    P4OUT &= (0xFF-0x01);
}
/*!
 * Turns on the red LED
 */
void __LEDRedOn()
{
    P4OUT |= 0x01;
}
/*!
 * @brief Toggles the green LED
 */
void __LEDGreenToggle()
{
    P1OUT ^= 0x40;
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
