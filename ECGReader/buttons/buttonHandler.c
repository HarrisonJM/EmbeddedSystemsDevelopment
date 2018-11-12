/*!
 * @brief Button handler for both buttons. Handles pressed(click), held, and double click
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include "buttons/private/buttonHandlingUtility.h"
#include "buttons/private/buttonS1Handling.h"
#include "buttons/private/buttonS2Handling.h"
/*!
 * @brief Initialises both Handlers' variables
 */
void InitButtonHandler()
{
    ButtonS1InitHandler();
    InitButtonS2Handler();
}

/*!
 * @brief handle the continuation of a state
 * @param button The button timer we wish to use
 */
void ButtonTimer(BUTTONSELECT_T button)
{
    switch(button)
    {
    case BUTTONS1:
        __ButtonS1Timer();
        break;
    case BUTTONS2:
        __ButtonS2Timer();
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
BUTTONSTATE_E GetButtonState(BUTTONSELECT_T button)
{
    switch(button)
    {
    case BUTTONS1:
        __ButtonS1GetState();
        break;
    case BUTTONS2:
        __GetButtonS2State();
        break;
    default:
        break;
    }
}
/*!
 * @brief Returns the number of times the button has been pressed
 * @param button The button that we want to get the number of presses for
 * @return The number of times the button has been pressed by the user
 */
int GetButtonNumberOfPresses(BUTTONSELECT_T button)
{
    switch(button)
    {
    case BUTTONS1:
        __ButtonS1GetNumberOfPresses();
        break;
    case BUTTONS2:
        __GetButtonS2NumberOfPresses();
        break;
    default:
        break;
    }
}
/*!
 * @brief Sets the number of Times The Button has been pressed
 * @param button The button for which we want to set the number of presses
 */
void SetButtonNumberOfPresses(BUTTONSELECT_T button, int newPresses)
{
    switch(button)
    {
    case BUTTONS1:
        __ButtonS1SetNumberOfPresses(newPresses);
        break;
    case BUTTONS2:
        __SetButtonS2NumberOfPresses(newPresses);
        break;
    default:
        break;
    }
}
