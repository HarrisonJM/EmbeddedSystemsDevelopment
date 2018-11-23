/*!
 * @brief Implementation for button handling
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include <buttons/buttonHandlingUtility.h>
#include "hardwareAbstractions/I_button.h"
#include "O_button.h"

#define INTERVAL_BUTTON_HANDLER 10 /* Divide by for interval in timer */
#define BUTTON_PRESS_TIME 100 /* The amount of time before a press is registered */
#define BUTTON_HELD_TIME 200 /*  The amount of time before a hold is registered */

#define DOUBLE_CLICK_COUNTER 100 /* Used to measure the time inbetween button releases */

/* Prototype for common function */
static void ButtonEnterState(ButtonStore_t* buttonStore,
                             const BUTTONSTATE_E newState);
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
void __ButtonSetNumberOfPresses(ButtonStore_t* buttonStore,
                                const int newPresses)
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
    buttonStore->buttonState = BUTTON_RELEASED;
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
    buttonStore->buttonpressTime++;
    if (buttonStore->ReadButton() != 0)
    {
        /* Released */
        if (buttonStore->buttonpressTime >= (BUTTON_PRESS_TIME/INTERVAL_BUTTON_HANDLER))
        {
            buttonStore->buttonNumberOfPresses++;
        }
        ButtonEnterState(buttonStore, BUTTON_RELEASED);
    }
    else
    {
        /* Still pressed */
        if (buttonStore->buttonpressTime >= (BUTTON_HELD_TIME/INTERVAL_BUTTON_HANDLER))
        {
            ButtonEnterState(buttonStore, BUTTON_HELD);
        }
    }
}
/*!
 * @brief How to handle the held state start
 * @param buttonStore A pointer to the button struct
 */
static void ButtonHeldEnter(ButtonStore_t* buttonStore)
{
    buttonStore->buttonpressTime = 0;
    buttonStore->buttonNumberOfPresses++;
}
/*!
 * @brief Handling the button continuing to be held
 * @param buttonStore A pointer to the button struct
 */
static void ButtonHeldTimer(ButtonStore_t* buttonStore)
{
    buttonStore->buttonpressTime++;

    if (buttonStore->ReadButton() != 0)
    {
        /* Released */
        ButtonEnterState(buttonStore, BUTTON_RELEASED);
    }
    else
    {
        /* Still pressed */
        if (buttonStore->buttonpressTime >= (BUTTON_HELD_TIME/INTERVAL_BUTTON_HANDLER))
        {
            ButtonEnterState(buttonStore, BUTTON_HELD);
        }
    }
}
/*!
 * @brief What to do while to button is released
 * @param buttonStore A pointer to the button struct
 */
static void ButtonReleaseTimer(ButtonStore_t* buttonStore)
{
    if (buttonStore->ReadButton() == 0)
    {
        /* Pressed */
        ButtonEnterState(buttonStore, BUTTON_PRESSED);
    }
}
/*!
 * @brief Enter the new button state
 * @param buttonStore Pointer to the button struct
 * @param newState The new state the button will take
 */
static void ButtonEnterState(ButtonStore_t* buttonStore,
                             const BUTTONSTATE_E newState)
{
    switch (newState)
    {
    case BUTTON_NULL:
        break;
    case BUTTON_RELEASED:
        break;
    case BUTTON_PRESSED:
        ButtonPressedEnter(buttonStore);
        break;
    case BUTTON_HELD:
        ButtonHeldEnter(buttonStore);
        break;
    case BUTTON_DOUBLE_CLICK:
    case BUTTON_DOUBLE_CLICK_HELD:
    default:
        break;
    }

    /* Set new state */
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
    case BUTTON_PRESSED:
        ButtonPressedTimer(buttonStore);
        break;
    case BUTTON_HELD:
        ButtonHeldTimer(buttonStore);
        break;
    case BUTTON_DOUBLE_CLICK:
    case BUTTON_DOUBLE_CLICK_HELD:
    default:
        break;
    }
}
