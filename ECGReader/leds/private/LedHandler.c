/*!
 * @brief Implementationf or public interface functions
 * @author Harrison J Marcks
 * @date 23/11/2018
 * @todo Extend this to be more useful
 */

#include "O_LED.h"
#include "leds/LedHandlerUtility.h"
#include "buttons/buttonHandlingUtility.h"
#include "LedGenericHandler.h"

/* LED objects */
static LEDSTORE_T greenStore;
static LEDSTORE_T redStore;

/*!
 * @brief Initialise led related things
 */
void LEDInitHandlerBothLEDs()
{
    LEDGreenInit(&greenStore);
    LEDRedInit(&redStore);
    LEDStoreInit(&greenStore);
    LEDStoreInit(&redStore);
}
/*!
 * @brief Returns the current state to the user
 * @param button enum of the button we wish to reference
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
LEDSTATE_T LEDGetState(const LEDSELECT_T led)
{
    LEDSTATE_T ledState = LED_NULL;
    switch(led)
    {
    case LEDGREEN:
        ledState = __LEDGetState(&greenStore);
        break;
    case LEDRED:
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
 */
void LEDTimer(const LEDSELECT_T led,
              const BUTTONSELECT_T button)
{
    switch(led)
    {
    case LEDGREEN:
        __LEDHandler(&redStore,
                     button);
        break;
    case LEDRED:
        __LEDHandler(&greenStore,
                     button);
        break;
    }
}
