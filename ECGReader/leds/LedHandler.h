/*!
 * @brief Public LED handler interface
 * @author Harrison James Marcks
 * @date 23/11/18
 */

#ifndef __LEDHANDLER_H__
#define __LEDHANDLER_H__

#include "LedHandlerUtility.h"

/*!
 * @brief Initialise button related things
 */
extern void LEDInitHandlerBothLEDs();
/*!
 * @brief Returns the current state to the user
 * @param button enum of the button we wish to reference
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
extern BUTTONSTATE_E LEDGetState(const LEDSELECT_T led);
/*!
 * @brief Run the entire LED Handler
 * @param led The LED selector for the LED we wish to handle
 */
/*!
 * @brief Run the entire LED Handler
 * @param led The LED selector for the LED we wish to handle
 * @param button The button selector that we are acting on
 */
extern void LEDTimer(const LEDSELECT_T led,
              const BUTTONSELECT_T button);

#endif /* __LEDHANDLER_H__ */
