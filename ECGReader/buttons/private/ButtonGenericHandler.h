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

BUTTONSTATE_E __ButtonGetState(ButtonStore_t* buttonStore);
int __ButtonGetNumberOfPresses(ButtonStore_t* buttonStore);
void __ButtonSetNumberOfPresses(ButtonStore_t* buttonStore,
                                const int newPresses);
void ButtonInitHandler(ButtonStore_t* buttonStore);
void __ButtonTimer(ButtonStore_t* buttonStore);

#endif /* __BUTTON_GENERIC_HANDLER_H__ */
