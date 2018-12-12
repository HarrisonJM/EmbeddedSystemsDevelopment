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
extern void __LEDHardwareInit(void);
/*!
 * @brief Toggles the red LED
 */
extern void __LEDRedToggle(void);
/*!
 * @brief Turns off the red LED
 */
extern void __LEDRedOff(void);
/*!
 * @brief Turns on the red LED
 */
extern void __LEDRedOn(void);
/*!
 * @brief Toggles the green LED
 */
extern void __LEDGreenToggle(void);
/*!
 * @brief Turns off the green LED
 */
extern void __LEDGreenOff(void);
/*!
 * @brief Turns on the green LED
 */
extern void __LEDGreenOn(void);

#endif /* __I_LEDS_H__ */
