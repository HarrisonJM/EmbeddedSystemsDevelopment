/*!
 * @brief An LED handler for interacting with the button handler more effectively
 * @author Harrison J Marcks
 * @date 23/11/18
 */

#include "O_LED.h"
#include "../LedHandlerUtility.h"
#include "buttons/buttonHandler.h"

/* How often the LEDs are interacted with */
#define LED_PERIOD 50
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
LEDSTATE_T __LEDGetState(LEDSTORE_T *ledStore)
{
    return ledStore->state;
}
/*!
 * @brief handles LEDs uniformly, but only for button presses, so actually a bit useless atm
 * @param ledStore A pointer to the LED we wish to use
 * @param button The button selector for the button that's controlling the LED
 */
void __LEDHandler(LEDSTORE_T* ledStore,
                  BUTTONSELECT_T button)
{
    ledStore->period++;
    if (ledStore->period >= LED_PERIOD)
    {
        ledStore->period = 0;
        switch (ledStore->state)
        {
        case LED_OFF:
            if (ButtonGetNumberOfPresses(button) > 0)
            {
                ButtonSetNumberOfPresses(button,
                                         ButtonGetNumberOfPresses(button)-1);
                ledStore->LEDOn();
                ledStore->state = LED_ON;
            }
            else
            {
                ledStore->state = LED_ON;
            }
            break;
        case LED_ON:
            ledStore->LEDOff();
            ledStore->state = LED_OFF;
            break;
        default:
            break;
        }
    }
}
