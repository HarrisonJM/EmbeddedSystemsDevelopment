/*!
 * @brief Implementation for buttonS2 handling
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include "buttonHandlingUtility.h"

void EnterButtonS2State(int new_state);

/* Private */
static int buttonS2NumberOfPresses;
static int buttonS2State;
static int buttonS2pressTime;
static int buttonS2ReleaseTime;

/* Mutators/Accessors */
/*!
 * @brief Returns the current state to the user
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
BUTTONSTATE_E GetButtonS2State()
{
    return buttonS2State;
}
/*!
 * @brief Returns the number of times the button has been pressed
 * @return The number of times the button has been pressed by the user
 */
int GetButtonS2NumberOfPresses()
{
    return buttonS2NumberOfPresses;
}
/*!
 * @brief Sets the number of Times The Button has been pressed
 */
void SetButtonS2NumberOfPresses(int newPresses)
{
    buttonS2NumberOfPresses = newPresses;
}

/* Functions */
/*!
 * @brief Iinitialises our button's variables
 */
void InitButtonS2Handler()
{
    buttonS2State = BUTTON_NULL;
    buttonS2NumberOfPresses = 0;
    buttonS2pressTime = 0;
    buttonS2ReleaseTime = 0;
}
/*!
 * @brief Resets the pressed timer
 */
void ButtonS2PressedEnter()
{
    buttonS2pressTime = 0;
}
/*!
 * @brief Measures the amount of time the button is pressed. Handles debouncing
 */
void ButtonS2PressedTimer()
{
    buttonS2pressTime++;
    if (ReadButtonS2() != 0)
    {
        // Released
        if (buttonS2pressTime >= (MINIMUM_BUTTON_INTERACTION_TIME/INTERVAL_BUTTON_HANDLER))
        {
            buttonS2NumberOfPresses++;
        }
        EnterButtonS2State(BUTTON_RELEASED);
    }
    else
    {
        // Still pressed
        if (buttonS2pressTime >= (BUTTON_HELD_TIME/INTERVAL_BUTTON_HANDLER))
        {
            EnterButtonS2State(BUTTON_HELD);
        }
    }
}
/*!
 * @brief How to handle the held state start
 */
void ButtonS2HeldEnter()
{
    buttonS2pressTime = 0;
    buttonS2NumberOfPresses++;
}
/*!
 * @brief Handling the button continuing to be held
 */
void ButtonS2HeldTimer()
{
    buttonS2pressTime++;
    if (ReadButtonS2() != 0)
    {
        // Released
        EnterButtonS2State(BUTTON_RELEASED);
    }
    else
    {
        // Still pressed
        if (buttonS2pressTime >= (BUTTON_HELD_TIME/INTERVAL_BUTTON_HANDLER))
        {
            EnterButtonS2State(BUTTON_HELD);
        }
    }
}
/*!
 * @brief What to do while to button is released
 */
void ButtonS2ReleaseTimer()
{
    if (ReadButtonS2() == 0)
    {
        if (buttonS2ReleaseTime >= (MINIMUM_BUTTON_INTERACTION_TIME/INTERVAL_BUTTON_HANDLER))
        {
            buttonS2ReleaseTime = 0;
            buttonS2State = BUTTON_PRESSED;
        }
    }
}
/*!
 * @brief Enter the new button state
 */
void EnterButtonS2State(int new_state)
{
    switch (new_state)
    {
    case BUTTON_NULL:
        break;
    case BUTTON_RELEASED:
        break;
    case BUTTON_PRESSED:
        ButtonS2PressedEnter();
        break;
    case BUTTON_HELD:
        ButtonS2HeldEnter();
        break;
    default:
        break;
    }

    buttonS2State = new_state;
}
/*!
 * @brief handle the continuation of a state
 */
void ButtonS2Timer()
{
    switch (buttonS2State)
    {
    case BUTTON_NULL:
        break;
    case BUTTON_RELEASED:
        ButtonS2ReleaseTimer();
        break;
    case BUTTON_PRESSED:
        ButtonS2PressedTimer();
        break;
    case BUTTON_HELD:
        ButtonS2HeldTimer();
        break;
    default:
        break;
    }
}

