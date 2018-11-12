/*!
 * @brief links the hardware implementation with the abstracted interfaces
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include "hardwareAbstractions/I_led.h"
#include "ledUse.h"

void CreateLEDLinks()
{
    LEDOnGreen = &__LEDGreenOn;
    LEDOffGreen = &__LEDGreenOff;
    LEDToggleGreen = &__LEDGreenToggle;

    LEDOnRed = &__LEDRedOn;
    LEDOffRed = &__LEDRedOff;
    LEDToggleRed = &__LEDRedToggle;
}
