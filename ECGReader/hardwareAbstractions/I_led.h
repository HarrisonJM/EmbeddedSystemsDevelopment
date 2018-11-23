/*!
 * @brief LED functions for using the LEDs
 * @author Harrison J Marcks
 * @date 12/11/18
 */

#ifndef __I_LEDS_H__
#define __I_LEDS_H__

/*!
 * @brief inits the LEDHardware
 */
extern void __LEDHardwareInit();
/*!
 * @brief Toggles the red LED
 */
extern void __LEDRedToggle();
/*!
 * @brief Turns off the red LED
 */
extern void __LEDRedOff();
/*!
 * @brief Turns on the red LED
 */
extern void __LEDRedOn();
/*!
 * @brief Toggles the green LED
 */
extern void __LEDGreenToggle();
/*!
 * @brief Turns off the green LED
 */
extern void __LEDGreenOff();
/*!
 * @brief Turns on the green LED
 */
extern void __LEDGreenOn();

#endif /* __I_LEDS_H__ */
