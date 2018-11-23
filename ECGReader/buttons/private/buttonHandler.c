/*!
 * @brief Button handler for both buttons. Handles pressed(click), held, and double click
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include "O_button.h"
#include "../buttonHandlingUtility.h"
#include "ButtonGenericHandler.h"

static ButtonStore_t S1;
static ButtonStore_t S2;

/*!
 * @brief Initialises Handler variables
 */
void ButtonInitHandlerBothButtons()
{
    ButtonS1Init(&S1);
    ButtonS2Init(&S2);
    ButtonInitHandler(&S1);
    ButtonInitHandler(&S2);
}
/*!
 * @brief handle the continuation of a state
 * @param button The button timer we wish to use
 */
void ButtonTimer(BUTTONSELECT_T button)
{
    switch (button)
    {
    case BUTTONS1:
        __ButtonTimer(&S1);
        break;
    case BUTTONS2:
        __ButtonTimer(&S2);
        break;
    default:
        break;
    }
}
/*!
 * @brief Returns the current state to the user
 * @param button The button state we wish to get
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
int ButtonGetState(const BUTTONSELECT_T button)
{
    int state = BUTTON_NULL;
    switch (button)
    {
    case BUTTONS1:
        state = __ButtonGetState(&S1);
        break;
    case BUTTONS2:
        state = __ButtonGetState(&S2);
        break;
    default:
        break;
    }

    return state;
}
/*!
 * @brief Returns the number of times the button has been pressed
 * @param button The button that we want to get the number of presses for
 * @return The number of times the button has been pressed by the user
 */
int ButtonGetNumberOfPresses(const BUTTONSELECT_T button)
{
    int buttonPressNum = 0;
    switch (button)
    {
    case BUTTONS1:
        buttonPressNum = __ButtonGetNumberOfPresses(&S1);
        break;
    case BUTTONS2:
        buttonPressNum = __ButtonGetNumberOfPresses(&S2);
        break;
    default:
        break;
    }

    return buttonPressNum;
}
/*!
 * @brief Sets the number of Times The Button has been pressed
 * @param button The button for which we want to set the number of presses
 * @param newPresses The value for the new number of presses the button should take
 */
void ButtonSetNumberOfPresses(const BUTTONSELECT_T button,
                              const int newPresses)
{
    switch (button)
    {
    case BUTTONS1:
        __ButtonSetNumberOfPresses(&S1, newPresses);
        break;
    case BUTTONS2:
        __ButtonSetNumberOfPresses(&S2, newPresses);
        break;
    default:
        break;
    }
}
