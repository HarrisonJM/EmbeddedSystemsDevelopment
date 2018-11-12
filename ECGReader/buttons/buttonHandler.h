/*!
 * @brief Public declarations for the button handler
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#ifndef __BUTTON_HANDLER_H__
#define __BUTTON_HANDLER_H__

void ButtonInitHandler();

/*!
 * @brief handle the continuation of a state
 */
void ButtonTimer(BUTTONSELECT_T button);
/*!
 * @brief Returns the current state to the user
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
BUTTONSTATE_E ButtonGetState(BUTTONSELECT_T button);
/*!
 * @brief Returns the number of times the button has been pressed
 * @return The number of times the button has been pressed by the user
 */
int ButtonGetNumberOfPresses(BUTTONSELECT_T button);
/*!
 * @brief Sets the number of Times The Button has been pressed
 */
void ButtonSetNumberOfPresses(BUTTONSELECT_T button,
                              int newPresses);

#endif /* __BUTTON_HANDLER_H__ */
