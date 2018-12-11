/*!
 * @brief An LED handler for tracking the state of the buttons
 * @author Harrison J Marcks
 * @date 23/11/18
 */

#include <helpers/eventQueue/eventQueue.h>
#include "O_LED.h"
#include "../LedHandlerUtility.h"
#include "buttons/buttonHandlingUtility.h"

/* Definitions */
/*! @brief How often the LEDs are interacted with */
#define LED_PERIOD 50

/* Prototypes */
static void __LEDTurnOn(LEDSTORE_T* ledStore);
static void __LEDTurnOff(LEDSTORE_T* ledStore);
/*!
 * @brief Initialises the LED "objects" with values
 * @param ledStore Pointer to the LED store we're init'ing
 */
void LEDStoreInit(LEDSTORE_T* ledStore)
{
    ledStore->state = LED_OFF;
    ledStore->period = 0;
}
/*!
 * @brief Returns the selected LEDs state
 * @param ledStore the ledStore we wish to get from
 */
LEDACTION_T __LEDGetState(LEDSTORE_T *ledStore)
{
    return ledStore->state;
}
/*!
 * @brief Handles LEDs uniformly, gives us a way to track, in software, what the lights are doing
 * @param ledStore A pointer to the LED we wish to use
 */
void __LEDHandler(LEDSTORE_T* ledStore
                  , const LEDACTION_T newState)
{
    switch(newState)
    {
    case LED_NULL:
    case LED_ON:
        __LEDTurnOn(ledStore);
        break;
    case LED_OFF:
        __LEDTurnOff(ledStore);
        break;
    case LED_TOGGLE:
        if(ledStore->state == LED_ON)
        {
            __LEDTurnOff(ledStore);
        }
        else
        {
            __LEDTurnOn(ledStore);
        }
        break;
    }
}
/*!
 * @brief turns the LED off
 * @param ledStore A pointer to the LED we wish to use
 */
static void __LEDTurnOn(LEDSTORE_T* ledStore)
{
    ledStore->LEDOn();
    ledStore->state = LED_ON;
}
/*!
 * @brief turns the LED off
 * @param ledStore A pointer to the LED we wish to use
 */
static void __LEDTurnOff(LEDSTORE_T* ledStore)
{
    ledStore->LEDOff();
    ledStore->state = LED_OFF;
}
