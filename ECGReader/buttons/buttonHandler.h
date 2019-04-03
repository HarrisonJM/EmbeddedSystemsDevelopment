/*!
 * @brief Public declarations for the button handler
 * @author Harrison J Marcks
 * @addtogroup buttons
 * @addtogroup private
 * @date 12/11/2018
 */

#ifndef __BUTTON_HANDLER_H__
#define __BUTTON_HANDLER_H__

#include "../helpers/eventQueue/eventQueue.h"
#include "buttonHandlingUtility.h"

/*!
 * @brief Initialise button related things
 */
extern void ButtonHandlerInitBothButtons(void);
/*!
 * @brief handle the continuation of a state
 * @param button enum of the button we wish to reference
 */
extern void ButtonTimer(const BUTTONSELECT_T button);
/*!
 * @brief Returns the current state to the user
 * @param button enum of the button we wish to reference
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
extern BUTTONSTATE_E ButtonGetState(const BUTTONSELECT_T button);
/*!
 * @brief Returns the number of times the button has been pressed
 * @param button enum of the button we wish to reference
 * @return The number of times the button has been pressed by the user
 */
extern int ButtonGetNumberOfPresses(const BUTTONSELECT_T button);
/*!
 * @brief Sets the number of Times The Button has been pressed
 * @param button enum of the button we wish to reference
 * @param newPresses The new humber of presses
 */
extern void ButtonSetNumberOfPresses(const BUTTONSELECT_T button,
                                     const int newPresses);
/*!
 * @brief Returns the address of the slected button's event queue
 * @param button The button we wish to get the queue for
 * @param queue An empty pointer we wish to set the queue to
 * @return The address for the selcted buttosn event queue
 */
EVENTQUEUE_T* ButtonGetQueue(const BUTTONSELECT_T button);

#endif /* __BUTTON_HANDLER_H__ */
