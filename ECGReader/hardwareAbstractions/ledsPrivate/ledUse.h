/*!
 * @brief declaration for non-hardware agnostic implementation of LED usage
 */

#ifndef __LED_USE_H__
#define __LED_USE_H__

/*!
 * @brief inits the LEDs
 */
void __LEDHardwareInit();
/*!
 * @brief Toggles the red LED
 */
void __LEDRedToggle();
/*!
 * Turns off the red LED
 */
void __LEDRedOff();
/*!
 * Turns on the red LED
 */
void __LEDRedOn();
/*!
 * @brief Toggles the green LED
 */
void __LEDGreenToggle();
/*!
 * @brief Turns off the green LED
 */
void __LEDGreenOff();
/*!
 * @brief Turns on the green LED
 */
void __LEDGreenOn();

#endif /* __LED_USE_H__ */
