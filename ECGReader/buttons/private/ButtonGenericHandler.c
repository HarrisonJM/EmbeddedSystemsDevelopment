/*!
 * @brief Implementation for button handling
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include <buttons/buttonHandlingUtility.h>
#include "hardwareAbstractions/I_button.h"
#include "O_button.h"

static void ButtonEnterState(ButtonStore_t* buttonStore, int newState);
inline static void HeldEnter(ButtonStore_t* buttonStore);
inline static void HeldTimer(ButtonStore_t* buttonStore, BUTTONSTATE_E finalState);
inline static void PressTimer(ButtonStore_t* buttonStore, BUTTONSTATE_E finalState);
inline static void ReleaseTimer(ButtonStore_t* buttonStore);

/* Mutators/Accessors */
/*!
 * @brief Returns the current state to the user
 * @param buttonStore A pointer to the button struct
 * @return The state the button is currently in as defined by BUTTONSTATE_E
 */
BUTTONSTATE_E __ButtonGetState(ButtonStore_t* buttonStore)
{
    return buttonStore->buttonState;
}
/*!
 * @brief Returns the number of times the button has been pressed
 * @param buttonStore A pointer to the button struct
 * @return The number of times the button has been pressed by the user
 */
int __ButtonGetNumberOfPresses(ButtonStore_t* buttonStore)
{
    return buttonStore->buttonNumberOfPresses;
}
/*!
 * @brief Sets the number of Times The Button has been pressed
 *
 * Should only really be used for decrementing the button presses when performing some function
 *
 * @param buttonStore A pointer to the button struct
 * @param newPresses The new number of presses
 */
void __ButtonSetNumberOfPresses(ButtonStore_t* buttonStore, int newPresses)
{
    buttonStore->buttonNumberOfPresses = newPresses;
}


/* Functions */
/*!
 * @brief Initialises our button's variables
 * @param buttonStore A pointer to the button struct
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
 * @param buttonStore A pointer to the button struct
 */
static void ButtonPressedEnter(ButtonStore_t* buttonStore)
{
    buttonStore->buttonpressTime = 0;
}
/*!
 * @brief Measures the amount of time the button is pressed. Handles debouncing
 * @param buttonStore A pointer to the button struct
 */
static void ButtonPressedTimer(ButtonStore_t* buttonStore)
{
    PressTimer(buttonStore, BUTTON_HELD);
}
/*!
 * @brief How to handle the held state start
 * @param buttonStore A pointer to the button struct
 */
static void ButtonHeldEnter(ButtonStore_t* buttonStore)
{
    buttonStore->buttonpressTime = 0;
}
/*!
 * @brief Handling the button continuing to be held
 * @param buttonStore A pointer to the button struct
 */
static void ButtonHeldTimer(ButtonStore_t* buttonStore)
{
    HeldTimer(buttonStore, BUTTON_HELD);
}
/*!
 * @brief What to do while to button is released
 * @param buttonStore A pointer to the button struct
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
 * @param buttonStore A pointer to the button struct
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
 * @param buttonStore A pointer to the button struct
 */
static void ButtonDoubleClickEnter(ButtonStore_t* buttonStore)
{
    buttonStore->buttonpressTime = 0;
}
/*!
 * @brief Handles the "double click" state
 * @param buttonStore A pointer to the button struct
 */
static void ButtonDoubleClickTimer(ButtonStore_t* buttonStore)
{
    PressTimer(buttonStore, BUTTON_DOUBLE_CLICK_HELD);
}
/*!
 * @brief Handles a "double click" held state
 * @param buttonStore A pointer to the button struct
 */
static void ButtonDoubleClickHeldEnter(ButtonStore_t* buttonStore)
{
    HeldEnter(buttonStore);
}
/*!
 * @brief Handles the "double click held event"
 * @param buttonStore A pointer to the button struct
 */
static void ButtonDoubleClickHeldTimer(ButtonStore_t* buttonStore)
{
    HeldTimer(buttonStore, BUTTON_DOUBLE_CLICK_HELD);
}
/*!
 * @brief Enter the new button state
 * @param buttonStore Pointer to the button struct
 * @param newState The new state the button will take
 */
static void ButtonEnterState(ButtonStore_t* buttonStore, int newState)
{
    switch (newState)
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

    buttonStore->buttonState = newState;
}
/*!
 * @brief Handle the continuation of a state
 * @param buttonStore A pointer to the button struct
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
 * @param buttonStore A pointer to the button struct
 */
static inline void HeldEnter(ButtonStore_t* buttonStore)
{
    buttonStore->buttonpressTime = 0;
    buttonStore->buttonNumberOfPresses++;
}
/*!
 * @brief Generic function for handling all held timers
 * @param buttonStore A pointer to the button struct
 * @param finalState What the final state will be
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
 * @param buttonStore Pointer to button struct
 * @param finalState The final state the button will take
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
 * @param buttonStore Pointer to button struct
 */
inline static void ReleaseTimer(ButtonStore_t* buttonStore)
{
    buttonStore->buttonReleaseTime = 0;
    buttonStore->buttonState = BUTTON_PRESSED;
}
