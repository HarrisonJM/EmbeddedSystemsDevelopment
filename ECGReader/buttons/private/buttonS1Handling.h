/*!
 * @brief Public Declarations for the button handling
 * @author Harrison J Marcks
 * @date 12/11/2018
 */
#ifndef __BUTTONS1HANDLING_H_
#define __BUTTONS1HANDLING_H_

#include "buttonHandlingUtility.h"

/*!
 * @brief handle the continuation of a state
 */
void __ButtonS1Timer();
/*!
 * @brief Returns the current state to the user
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
BUTTONSTATE_E __ButtonS1GetState();
/*!
 * @brief Returns the number of times the button has been pressed
 * @return The number of times the button has been pressed by the user
 */
int __ButtonS1GetNumberOfPresses();
/*!
 * @brief Sets the number of Times The Button has been pressed
 */
void __ButtonS1SetNumberOfPresses(int newPresses);

#endif /* __BUTTONS1HANDLING_H_ */
