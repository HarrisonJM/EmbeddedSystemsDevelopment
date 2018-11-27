/*!
 * @brief Generic Handler public declarations
 *
 * @author Harrison J Marcks
 *
 * @date 19/11/2018
 */
#include "O_button.h"
#include "../buttonHandlingUtility.h"

#ifndef __BUTTON_GENERIC_HANDLER_H__
#define __BUTTON_GENERIC_HANDLER_H__

/*!
 * @brief Inits the handler for the button
 * @param butonStore A pointer to the buttonstore
 */
void ButtonInitHandler(ButtonStore_t* buttonStore);
/*!
 * @brief Returns the state of the button pointed to by buttonStore
 * @param buttonStore A pointer to the button store
 * @return The state of the button
 */
BUTTONSTATE_E __ButtonGetState(ButtonStore_t* buttonStore);
/*!
 * @brief Returns the number fo times the slected button has been pressed
 * @param buttonStore A pointer to the buttonstore
 * @return The number of times the button has been pressed
 */
int __ButtonGetNumberOfPresses(ButtonStore_t* buttonStore);
/*!
 * @brief Sets the buttons current number of presses
 * @param buttonStore A pointer to the buttonstore
 * @param newPresses the new number of presses the button should take
 */
void __ButtonSetNumberOfPresses(ButtonStore_t* buttonStore,
                                const int newPresses);
/*!
 * @brief Runs the button timer for the selected button handler
 * @param buttonStore A pointer to the buttonstore
 */
void __ButtonTimer(ButtonStore_t* buttonStore);
/*!
 * @brief returns the buttons event queue as a pointer
 * @param buttonStore A pointer to the buttonstore
 * @return A pointer to the button's event queue
 */
EVENTQUEUE_T* __ButtonGetEventQueue(ButtonStore_t* buttonStore);

#endif /* __BUTTON_GENERIC_HANDLER_H__ */
