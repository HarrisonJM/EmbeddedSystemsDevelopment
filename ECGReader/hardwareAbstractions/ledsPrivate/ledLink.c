/*!
 * @brief links the hardware implementation with the abstracted interfaces
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include <hardwareAbstractions/ledsPrivate/ledUse.h>
#include "hardwareAbstractions/I_led.h"

void CreateLEDLinks()
{
    LEDHardwareInit = &__LEDHardwareInit;
    LEDOnGreen = &__LEDGreenOn;
    LEDOffGreen = &__LEDGreenOff;
    LEDToggleGreen = &__LEDGreenToggle;

    LEDOnRed = &__LEDRedOn;
    LEDOffRed = &__LEDRedOff;
    LEDToggleRed = &__LEDRedToggle;
}
