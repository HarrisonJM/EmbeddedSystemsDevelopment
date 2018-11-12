/*!
 * @brief Implementation for buttonS1 handling
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include <buttons/buttonHandlingUtility.h>
#include "hardwareAbstractions/I_button.h"

static void ButtonS1EnterState(int new_state);
inline static void HeldEnter();
inline static void HeldTimer(BUTTONSTATE_E finalState);
inline static void PressTimer(BUTTONSTATE_E finalState);

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
BUTTONSTATE_E __ButtonS1GetState()
{
    return buttonS1State;
}
/*!
 * @brief Returns the number of times the button has been pressed
 * @return The number of times the button has been pressed by the user
 */
int __ButtonS1GetNumberOfPresses()
{
    return buttonS1NumberOfPresses;
}
/*!
 * @brief Sets the number of Times The Button has been pressed
 */
void __ButtonS1SetNumberOfPresses(int newPresses)
{
    buttonS1NumberOfPresses = newPresses;
}


/* Functions */
/*!
 * @brief Iinitialises our button's variables
 */
void ButtonS1InitHandler()
{
    buttonS1State = BUTTON_NULL;
    buttonS1NumberOfPresses = 0;
    buttonS1pressTime = 0;
    buttonS1ReleaseTime = 0;
}
/*!
 * @brief Resets the pressed timer
 */
static void ButtonS1PressedEnter()
{
    buttonS1pressTime = 0;
}
/*!
 * @brief Measures the amount of time the button is pressed. Handles debouncing
 */
static void ButtonS1PressedTimer()
{
    PressTimer(BUTTON_HELD);
}
/*!
 * @brief How to handle the held state start
 */
static void ButtonS1HeldEnter()
{
    buttonS1pressTime = 0;
}
/*!
 * @brief Handling the button continuing to be held
 */
static void ButtonS1HeldTimer()
{
    HeldTimer(BUTTON_HELD);
}
/*!
 * @brief What to do while to button is released
 */
static void ButtonS1ReleaseTimer()
{
    if (ReadButtonS1() == 0)
    {
        if (buttonS1ReleaseTime >= (MINIMUM_BUTTON_INTERACTION_TIME/INTERVAL_BUTTON_HANDLER))
        {
            ReleaseTimer();
        }
    }
}
/*!
 * @brief Handles timing for the semi-released state
 */
static void ButtonS1SemiReleaseTimer()
{
    if (ReadButtonS1() == 0)
    {
        if (buttonS1ReleaseTime <= (DOUBLE_CLICK_COUNTER/INTERVAL_BUTTON_HANDLER))
        {
            buttonS1ReleaseTime = 0;
            buttonS1State = BUTTON_DOUBLE_CLICK;
        }
        else if (buttonS1ReleaseTime >= (MINIMUM_BUTTON_INTERACTION_TIME/INTERVAL_BUTTON_HANDLER))
        {
            ReleaseTimer();
        }
        else if (buttonS1ReleaseTime > (MINIMUM_BUTTON_INTERACTION_TIME/INTERVAL_BUTTON_HANDLER))
        {
            ButtonEnterS1State(BUTTON_RELEASED);
        }
    }
}
/*!
 * @brief Handles A double Click
 */
static void ButtonS1DoubleClickEnter()
{
    buttonS1pressTime = 0;
}
/*!
 * @brief Handles the "double click" state
 */
static void ButtonS1DoubleClickTimer()
{
    PressTimer(BUTTON_DOUBLE_CLICK_HELD);
}
/*!
 * @brief Handles a "double click" held state
 */
static void ButtonS1DoubleClickHeldEnter()
{
    HeldEnter();
}
/*!
 * @brief Handles the "double click held event"
 */
static void ButtonS1DoubleClickHeldTimer()
{
    HeldTimer(BUTTON_DOUBLE_CLICK_HELD);
}
/*!
 * @brief Enter the new button state
 */
static void ButtonS1EnterState(int new_state)
{
    switch (new_state)
    {
    case BUTTON_NULL:
        break;
    case BUTTON_RELEASED:
        break;
    case BUTTON_SEMI_RELEASED:
        break;
    case BUTTON_PRESSED:
        ButtonS1PressedEnter();
        break;
    case BUTTON_HELD:
        ButtonS1HeldEnter();
        break;
    case BUTTON_DOUBLE_CLICK:
        ButtonS1DoubleClickEnter();
    case BUTTON_DOUBLE_CLICK_HELD:
        ButtonS1DoubleClickHeldEnter();
    default:
        break;
    }

    buttonS1State = new_state;
}
/*!
 * @brief handle the continuation of a state
 */
void __ButtonS1Timer()
{
    switch (buttonS1State)
    {
    case BUTTON_NULL:
        break;
    case BUTTON_RELEASED:
        ButtonS1ReleaseTimer();
        break;
    case BUTTON_SEMI_RELEASED:
        ButtonS1SemiReleaseTimer();
        break;
    case BUTTON_PRESSED:
        ButtonS1PressedTimer();
        break;
    case BUTTON_HELD:
        ButtonS1HeldTimer();
        break;
    case BUTTON_DOUBLE_CLICK:
        ButtonS1DoubleClickTimer();
    case BUTTON_DOUBLE_CLICK_HELD:
        ButtonS1DoubleClickHeldTimer();
    default:
        break;
    }
}
/*!
 * @brief Handles entering a Held state
 */
static inline void HeldEnter()
{
    buttonS1pressTime = 0;
    buttonS1NumberOfPresses++;
}
/*!
 * @brief Generic function for handling all held timers
 */
static inline void HeldTimer(BUTTONSTATE_E finalState)
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
            EnterButtonS1State(finalState);
        }
    }
}
/*!
 * @brief Generic handler for "pressed" states
 */
static inline void PressTimer(BUTTONSTATE_E finalState)
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
            EnterButtonS1State(finalState);
        }
    }
}
/*!
 * @brief Release timer for normal Release
 */
inline static void ReleaseTimer()
{
    buttonS1ReleaseTime = 0;
    buttonS1State = BUTTON_PRESSED;
}
