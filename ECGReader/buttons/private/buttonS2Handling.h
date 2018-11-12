/*!
 * @brief Public Declarations for the button handler
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#ifndef __BUTTONS2HANDLING_H_
#define __BUTTONS2HANDLING_H_

#include "../buttonHandlingUtility.h"

/*!
 * @brief handle the continuation of a state
 */
void __ButtonS2Timer();
/*!
 * @brief Returns the current state to the user
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
BUTTONSTATE_E __ButtonGetS2State();
/*!
 * @brief Returns the number of times the button has been pressed
 * @return The number of times the button has been pressed by the user
 */
int __ButtonGetS2NumberOfPresses();
/*!
 * @brief Sets the number of Times The Button has been pressed
 */
void __ButtonSetS2NumberOfPresses(int newPresses);

#endif /* __BUTTONS2HANDLING_H_ */
