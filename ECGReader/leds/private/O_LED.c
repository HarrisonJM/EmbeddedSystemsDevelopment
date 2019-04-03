/*!
 * @brief initilisation functions for the LED "object"
 * @author Harrison J Marcks
 * @date 23/11/18
 *
 * @addtogroup leds
 * @{
 * @addtogroup private
 * @{
 */

#include "O_LED.h"
#include "hardwareAbstractions/public/I_led.h"

/*!
 * @brief Assigns functions to the store's function pointers for the Red led
 * @param red Pointer to the Red LED store
 */
void LEDRedInit(LEDSTORE_T* red)
{
    red->LEDOn = __LEDRedOn;
    red->LEDOff = __LEDRedOff;
    red->LEDToggle = __LEDRedToggle;
}
/*!
 * @brief Assigns functions to the store's function pointers for the green led
 * @param green Pointer to the green LED store
 */
void LEDGreenInit(LEDSTORE_T* green)
{
    green->LEDOn = __LEDGreenOn;
    green->LEDOff = __LEDGreenOff;
    green->LEDToggle = __LEDGreenToggle;
}

/*! @} @} */
