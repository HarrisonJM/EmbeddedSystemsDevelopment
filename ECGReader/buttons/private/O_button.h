/*!
 * @brief Button Object header
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#ifndef __O_BUTTON_H__
#define __O_BUTTON_H__

#include "../../helpers/boollint.h"
#include "../buttonHandlingUtility.h"

/*!
 * @brief the button store object
 * This struct is used to track each button's state
 * across the same functions, limiting the number of handlers we need
 */
typedef struct Button
{
    bool (*ReadButton)();
    int buttonNumberOfPresses;
    BUTTONSTATE_E buttonState;
    int buttonpressTime;
    int buttonReleaseTime;

} ButtonStore_t;

void ButtonS1Init(ButtonStore_t* S1);
void ButtonS2Init(ButtonStore_t* S2);

#endif /* __O_BUTTON_H__ */
