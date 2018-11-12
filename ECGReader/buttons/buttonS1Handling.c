/*!
 * @brief Implementation for buttonS1 handling
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include "buttonHandlingUtility.h"

void EnterButtonS1State(int new_state);

/* Private */
static int buttonS1NumberOfPresses;
static int buttonS1State;
static int buttonS1pressTime;
static int buttonS1ReleaseTime;

/* Mutators/Accessors */
/*!
 * @brief Returns the current state to the user
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
BUTTONSTATE_E GetButtonS1State()
{
    return buttonS1State;
}
/*!
 * @brief Returns the number of times the button has been pressed
 * @return The number of times the button has been pressed by the user
 */
int GetButtonS1NumberOfPresses()
{
    return buttonS1NumberOfPresses;
}
/*!
 * @brief Sets the number of Times The Button has been pressed
 */
void SetButtonS1NumberOfPresses(int newPresses)
{
    buttonS1NumberOfPresses = newPresses;
}


/* Functions */
/*!
 * @brief Iinitialises our button's variables
 */
void InitButtonS1Handler()
{
    buttonS1State = BUTTON_NULL;
    buttonS1NumberOfPresses = 0;
    buttonS1pressTime = 0;
    buttonS1ReleaseTime = 0;
}
/*!
 * @brief Resets the pressed timer
 */
void ButtonS1PressedEnter()
{
    buttonS1pressTime = 0;
}
/*!
 * @brief Measures the amount of time the button is pressed. Handles debouncing
 */
void ButtonS1PressedTimer()
{
    buttonS1pressTime++;
    if (ReadButtonS1() != 0)
    {
        // Released
        if (buttonS1pressTime >= (MINIMUM_BUTTON_INTERACTION_TIME/INTERVAL_BUTTON_HANDLER))
        {
            buttonS1NumberOfPresses++;
        }
        EnterButtonS1State(BUTTON_RELEASED);
    }
    else
    {
        // Still pressed
        if (buttonS1pressTime >= (BUTTON_HELD_TIME/INTERVAL_BUTTON_HANDLER))
        {
            EnterButtonS1State(BUTTON_HELD);
        }
    }
}
/*!
 * @brief How to handle the held state start
 */
void ButtonS1HeldEnter()
{
    buttonS1pressTime = 0;
}
/*!
 * @brief Handling the button continuing to be held
 */
void ButtonS1HeldTimer()
{
    buttonS1pressTime++;
    if (ReadButtonS1() != 0)
    {
        // Released
        EnterButtonS1State(BUTTON_RELEASED);
    }
    else
    {
        // Still pressed
        if (buttonS1pressTime >= (BUTTON_HELD_TIME/INTERVAL_BUTTON_HANDLER))
        {
            EnterButtonS1State(BUTTON_HELD);
        }
    }
}
/*!
 * @brief What to do while to button is released
 */
void ButtonS1ReleaseTimer()
{
    if (ReadButtonS1() == 0)
    {
        if (buttonS1ReleaseTime >= (MINIMUM_BUTTON_INTERACTION_TIME/INTERVAL_BUTTON_HANDLER))
        {
            buttonS1ReleaseTime = 0;
            buttonS1State = BUTTON_PRESSED;
        }
    }
}
/*!
 * @brief Handles A double Click
 */
void ButtonS1DoubleClickEnter()
{
 // TODO:
}
/*!
 * @brief Enter the new button state
 */
void EnterButtonS1State(int new_state)
{
    switch (new_state)
    {
    case BUTTON_NULL:
        break;
    case BUTTON_RELEASED:
        break;
    case BUTTON_PRESSED:
        ButtonS1PressedEnter();
        break;
    case BUTTON_HELD:
        ButtonS1HeldEnter();
        break;
    default:
        break;
    }

    buttonS1State = new_state;
}
/*!
 * @brief handle the continuation of a state
 */
void ButtonS1Timer()
{
    switch (buttonS1State)
    {
    case BUTTON_NULL:
        break;
    case BUTTON_RELEASED:
        ButtonS1ReleaseTimer();
        break;
    case BUTTON_PRESSED:
        ButtonS1PressedTimer();
        break;
    case BUTTON_HELD:
        ButtonS1HeldTimer();
        break;
    case BUTTON_DOUBLE_CLICK:

    default:
        break;
    }
}

