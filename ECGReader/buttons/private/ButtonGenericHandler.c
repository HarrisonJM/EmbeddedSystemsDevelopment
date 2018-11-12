/*!
 * @brief Implementation for button handling
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include <buttons/buttonHandlingUtility.h>
#include "hardwareAbstractions/I_button.h"
#include "O_button.h"

static void ButtonEnterState(ButtonStore_t* buttonStore, int new_state);
inline static void HeldEnter(ButtonStore_t* buttonStore);
inline static void HeldTimer(ButtonStore_t* buttonStore, BUTTONSTATE_E finalState);
inline static void PressTimer(ButtonStore_t* buttonStore, BUTTONSTATE_E finalState);
inline static void ReleaseTimer(ButtonStore_t* buttonStore);

/* Mutators/Accessors */
/*!
 * @brief Returns the current state to the user
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
BUTTONSTATE_E __ButtonGetState(ButtonStore_t* buttonStore)
{
    return buttonStore->buttonState;
}
/*!
 * @brief Returns the number of times the button has been pressed
 * @return The number of times the button has been pressed by the user
 */
int __ButtonGetNumberOfPresses(ButtonStore_t* buttonStore)
{
    return buttonStore->buttonNumberOfPresses;
}
/*!
 * @brief Sets the number of Times The Button has been pressed
 */
void __ButtonSetNumberOfPresses(ButtonStore_t* buttonStore, int newPresses)
{
    buttonStore->buttonNumberOfPresses = newPresses;
}


/* Functions */
/*!
 * @brief Iinitialises our button's variables
 */
void ButtonInitHandler(ButtonStore_t* buttonStore)
{
    buttonStore->buttonState = BUTTON_NULL;
    buttonStore->buttonNumberOfPresses = 0;
    buttonStore->buttonpressTime = 0;
    buttonStore->buttonReleaseTime = 0;
}
/*!
 * @brief Resets the pressed timer
 */
static void ButtonPressedEnter(ButtonStore_t* buttonStore)
{
    buttonStore->buttonpressTime = 0;
}
/*!
 * @brief Measures the amount of time the button is pressed. Handles debouncing
 */
static void ButtonPressedTimer(ButtonStore_t* buttonStore)
{
    PressTimer(buttonStore, BUTTON_HELD);
}
/*!
 * @brief How to handle the held state start
 */
static void ButtonHeldEnter(ButtonStore_t* buttonStore)
{
    buttonStore->buttonpressTime = 0;
}
/*!
 * @brief Handling the button continuing to be held
 */
static void ButtonHeldTimer(ButtonStore_t* buttonStore)
{
    HeldTimer(buttonStore, BUTTON_HELD);
}
/*!
 * @brief What to do while to button is released
 */
static void ButtonReleaseTimer(ButtonStore_t* buttonStore)
{
    if (buttonStore->ReadButton() == 0)
    {
        if (buttonStore->buttonReleaseTime >= (MINIMUM_BUTTON_INTERACTION_TIME/INTERVAL_BUTTON_HANDLER))
        {
            ReleaseTimer(buttonStore);
        }
    }
}
/*!
 * @brief Handles timing for the semi-released state
 */
static void ButtonSemiReleaseTimer(ButtonStore_t* buttonStore)
{
    if (buttonStore->ReadButton() == 0)
    {
        if (buttonStore->buttonReleaseTime <= (DOUBLE_CLICK_COUNTER/INTERVAL_BUTTON_HANDLER))
        {
            buttonStore->buttonReleaseTime = 0;
            ButtonEnterState(buttonStore, BUTTON_DOUBLE_CLICK);
        }
        else if (buttonStore->buttonReleaseTime >= (MINIMUM_BUTTON_INTERACTION_TIME/INTERVAL_BUTTON_HANDLER))
        {
            ReleaseTimer(buttonStore);
        }
        else if (buttonStore->buttonReleaseTime > (MINIMUM_BUTTON_INTERACTION_TIME/INTERVAL_BUTTON_HANDLER))
        {
            ButtonEnterState(buttonStore, BUTTON_RELEASED);
        }
    }
}
/*!
 * @brief Handles A double Click
 */
static void ButtonDoubleClickEnter(ButtonStore_t* buttonStore)
{
    buttonStore->buttonpressTime = 0;
}
/*!
 * @brief Handles the "double click" state
 */
static void ButtonDoubleClickTimer(ButtonStore_t* buttonStore)
{
    PressTimer(buttonStore, BUTTON_DOUBLE_CLICK_HELD);
}
/*!
 * @brief Handles a "double click" held state
 */
static void ButtonDoubleClickHeldEnter(ButtonStore_t* buttonStore)
{
    HeldEnter(buttonStore);
}
/*!
 * @brief Handles the "double click held event"
 */
static void ButtonDoubleClickHeldTimer(ButtonStore_t* buttonStore)
{
    HeldTimer(buttonStore, BUTTON_DOUBLE_CLICK_HELD);
}
/*!
 * @brief Enter the new button state
 */
static void ButtonEnterState(ButtonStore_t* buttonStore, int new_state)
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
        ButtonPressedEnter(buttonStore);
        break;
    case BUTTON_HELD:
        ButtonHeldEnter(buttonStore);
        break;
    case BUTTON_DOUBLE_CLICK:
        ButtonDoubleClickEnter(buttonStore);
    case BUTTON_DOUBLE_CLICK_HELD:
        ButtonDoubleClickHeldEnter(buttonStore);
    default:
        break;
    }

    buttonStore->buttonState = new_state;
}
/*!
 * @brief handle the continuation of a state
 */
void __ButtonTimer(ButtonStore_t* buttonStore)
{
    switch (buttonStore->buttonState)
    {
    case BUTTON_NULL:
        break;
    case BUTTON_RELEASED:
        ButtonReleaseTimer(buttonStore);
        break;
    case BUTTON_SEMI_RELEASED:
        ButtonSemiReleaseTimer(buttonStore);
        break;
    case BUTTON_PRESSED:
        ButtonPressedTimer(buttonStore);
        break;
    case BUTTON_HELD:
        ButtonHeldTimer(buttonStore);
        break;
    case BUTTON_DOUBLE_CLICK:
        ButtonDoubleClickTimer(buttonStore);
    case BUTTON_DOUBLE_CLICK_HELD:
        ButtonDoubleClickHeldTimer(buttonStore);
    default:
        break;
    }
}
/*!
 * @brief Handles entering a Held state
 */
static inline void HeldEnter(ButtonStore_t* buttonStore)
{
    buttonStore->buttonpressTime = 0;
    buttonStore->buttonNumberOfPresses++;
}
/*!
 * @brief Generic function for handling all held timers
 */
static inline void HeldTimer(ButtonStore_t* buttonStore, BUTTONSTATE_E finalState)
{
    buttonStore->buttonpressTime++;
    if (buttonStore->ReadButton() != 0)
    {
        // Released
        EnterButtonState(buttonStore, BUTTON_RELEASED);
    }
    else
    {
        // Still pressed
        if (buttonStore->buttonpressTime >= (BUTTON_HELD_TIME/INTERVAL_BUTTON_HANDLER))
        {
            EnterButtonState(buttonStore, finalState);
        }
    }
}
/*!
 * @brief Generic handler for "pressed" states
 */
static inline void PressTimer(ButtonStore_t* buttonStore, BUTTONSTATE_E finalState)
{
    buttonStore->buttonpressTime++;
    if (buttonStore->ReadButton() != 0)
    {
        // Released
        if (buttonStore->buttonpressTime >= (MINIMUM_BUTTON_INTERACTION_TIME/INTERVAL_BUTTON_HANDLER))
        {
            buttonStore->buttonNumberOfPresses++;
        }

        EnterButtonState(BUTTON_RELEASED);
    }
    else
    {
        // Still pressed
        if (buttonStore->buttonpressTime >= (BUTTON_HELD_TIME/INTERVAL_BUTTON_HANDLER))
        {
            EnterButtonState(buttonStore, finalState);
        }
    }
}
/*!
 * @brief Release timer for normal Release
 */
inline static void ReleaseTimer(ButtonStore_t* buttonStore)
{
    buttonStore->buttonReleaseTime = 0;
    buttonStore->buttonState = BUTTON_PRESSED;
}
