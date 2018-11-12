/*!
 * @brief Implementation for buttonS2 handling
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include "buttons/private/buttonHandlingUtility.h"

void EnterButtonS2State(int new_state);
inline static void HeldEnter();
inline static void HeldTimer(BUTTONSTATE_E finalState);
inline static void PressTimer(BUTTONSTATE_E finalState);

/* Private */
static int buttonS2NumberOfPresses;
static int buttonS2State;
static int buttonS2pressTime;
static int buttonS2ReleaseTime;

/* Public Mutators/Accessors */
/*!
 * @brief Returns the current state to the user
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
BUTTONSTATE_E __GetButtonS2State()
{
    return buttonS2State;
}
/*!
 * @brief Returns the number of times the button has been pressed
 * @return The number of times the button has been pressed by the user
 */
int __GetButtonS2NumberOfPresses()
{
    return buttonS2NumberOfPresses;
}
/*!
 * @brief Sets the number of Times The Button has been pressed
 */
void __SetButtonS2NumberOfPresses(int newPresses)
{
    buttonS2NumberOfPresses = newPresses;
}

/* Private Functions */
/*!
 * @brief Iinitialises our button's variables
 */
static void InitButtonS2Handler()
{
    buttonS2State = BUTTON_NULL;
    buttonS2NumberOfPresses = 0;
    buttonS2pressTime = 0;
    buttonS2ReleaseTime = 0;
}
/*!
 * @brief Resets the pressed timer
 */
static void ButtonS2PressedEnter()
{
    buttonS2pressTime = 0;
}
/*!
 * @brief Measures the amount of time the button is pressed. Handles debouncing
 */
static void ButtonS2PressedTimer()
{
    PressTimer(BUTTON_HELD);
}
/*!
 * @brief How to handle the held state start
 */
static void ButtonS2HeldEnter()
{
    HeldEnter();
}
/*!
 * @brief Handling the button continuing to be held
 */
static void ButtonS2HeldTimer()
{
    HeldTimer(BUTTON_HELD);
}
/*!
 * @brief What to do while to button is released
 */
static void ButtonS2ReleaseTimer()
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
 * @brief Handles A double Click
 */
static void ButtonS2DoubleClickEnter()
{
    buttonS2pressTime = 0;
}
/*!
 * @brief Handles the "double click" state
 */
static void ButtonS2DoubleClickTimer()
{
    PressTimer(BUTTON_DOUBLE_CLICK_HELD);
}
/*!
 * @brief How to handle the held state start
 */
static void ButtonS2DoubleClickHeldEnter()
{
    HeldEnter();
}
/*!
 * @brief Handling the button continuing to be held
 */
static void ButtonS2DoubleClickHeldTimer()
{
    HeldTimer(BUTTON_DOUBLE_CLICK_HELD);
}
/*!
 * @brief Enter the new button state
 */
static void EnterButtonS2State(int new_state)
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
    case BUTTON_DOUBLE_CLICK:
        ButtonS2DoubleClickEnter();
    case BUTTON_DOUBLE_CLICK_HELD:
        ButtonS2DoubleClickHeldEnter();
        break;
    default:
        break;
    }

    buttonS2State = new_state;
}

/*!
 * @brief handle the continuation of a state
 */
void __ButtonS2Timer()
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
    case BUTTON_DOUBLE_CLICK:
        ButtonS2DoubleClickTimer();
    case BUTTON_DOUBLE_CLICK_HELD:
        ButtonS2DoubleClickHeldTimer();
        break;
    default:
        break;
    }
}
/*!
 * @brief Handles entering a Held state
 */
static inline void HeldEnter()
{
    buttonS2pressTime = 0;
    buttonS2NumberOfPresses++;
}
/*!
 * @brief Generic function for handling all held timers
 */
static inline void HeldTimer(BUTTONSTATE_E finalState)
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
            EnterButtonS2State(finalState);
        }
    }
}
/*!
 * @brief Generic handler for "pressed" states
 */
static inline void PressTimer(BUTTONSTATE_E finalState)
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
            EnterButtonS2State(finalState);
        }
    }
}
