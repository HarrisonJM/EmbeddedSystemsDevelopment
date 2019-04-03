/*!
 * @brief Implementationf or public interface functions
 * @author Harrison J Marcks
 * @date 23/11/2018
 *
 * @addtogroup leds
 * @{
 * @addtogroup private
 * @{
 */

#include "O_LED.h"
#include "leds/LedHandlerUtility.h"
#include "LedGenericHandler.h"

/* LED objects */
static LEDSTORE_T greenStore;
static LEDSTORE_T redStore;

/*!
 * @brief Initialise led related things
 */
void LEDHandlerInitBothLEDs()
{
    LEDGreenInit(&greenStore);
    LEDRedInit(&redStore);
    LEDStoreInit(&greenStore);
    LEDStoreInit(&redStore);
}
/*!
 * @brief Returns the current state to the user
 * @param led enum of the led we wish to reference
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
LEDACTION_T LEDGetState(const LEDSELECT_T led)
{
    LEDACTION_T ledState = LED_NULL;
    switch(led)
    {
    case LED_GREEN:
        ledState = __LEDGetState(&greenStore);
        break;
    case LED_RED:
        ledState = __LEDGetState(&redStore);
        break;
    default:
        break;
    }

    return ledState;
}
/*!
 * @brief Run the entire LED Handler
 * @param led The LED selector for the LED we wish to handle
 * @param newState The new state the LED should take
 */
void LEDUse(const LEDSELECT_T led
              , const LEDACTION_T newState)
{
    switch(led)
    {
    case LED_GREEN:
        __LEDHandler(&greenStore);
        break;
    case LED_RED:
        __LEDHandler(&redStore);
        break;
    }
}

/*! @} @} */
