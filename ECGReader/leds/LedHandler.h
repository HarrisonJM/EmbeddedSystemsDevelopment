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
extern void LEDHandlerInitBothLEDs(void);
/*!
 * @brief Returns the current state to the user
 * @param button enum of the button we wish to reference
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
extern LEDACTION_T LEDGetState(const LEDSELECT_T led);
/*!
 * @brief Run the entire LED Handler
 * @param led The LED selector for the LED we wish to handle
 * @param newState The new state the light should be
 */
extern void LEDUse(const LEDSELECT_T led
                   , const LEDACTION_T newState);

#endif /* __LEDHANDLER_H__ */
