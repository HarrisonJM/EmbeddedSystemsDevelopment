/*!
 * @brief Implementation for button handling
 * @author Harrison J Marcks
 * @addtogroup buttons
 * @addtogroup private
 * @date 12/11/2018
 */

#include <buttons/buttonHandlingUtility.h>
#include <helpers/eventQueue/eventQueue.h>
#include "hardwareAbstractions/public/I_button.h"
#include "O_button.h"

#define INTERVAL_BUTTON_HANDLER 10 /* Divide by for interval in timer (represents how often the timer function is triggered)  */
#define BUTTON_PRESS_TIME 100 /* The amount of time before a press is registered */
#define BUTTON_HELD_TIME 200 /*  The amount of time before a hold is registered */
#define DOUBLE_CLICK_COUNTER 100 /* Used to measure the time in between button releases */

/* Prototype for common function */
static void ButtonEnterState(ButtonStore_t* buttonStore,
                             const BUTTONSTATE_E newState);
/*! Accessors/Mutators */
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
/*!
 * @brief Returns the buttons event Queue
 * @param buttonStore A pointer to the button who's queue we want to get
 * @return The address of the buttons queue
 */
EVENTQUEUE_T* __ButtonGetEventQueue(ButtonStore_t* buttonStore)
{
    return &(buttonStore->buttonQueue);
}

/* Functions */
/*!
 * @brief Adds a button event
 * @param event The event to add
 * @param buttonStore A pointer to the button containing the store we're working with
 */
void ButtonAddEvent(const BUTTONSTATE_E event,
                    ButtonStore_t* buttonStore)
{
    EVENTQUEUE_T* q_p = &(buttonStore->buttonQueue);
    EVENT_T e;
    e.event = event;

    if(q_p->PushBack(q_p, &e) != true);
    {
        /*! @todo Handle this somehow */
    }
}
/*!
 * @brief Initialises our button store
 * @param buttonStore A pointer to the button struct
 */
void ButtonInitHandler(ButtonStore_t* buttonStore)
{
    buttonStore->buttonState = EVENT_BUTTON_RELEASED;
    buttonStore->buttonNumberOfPresses = 0;
    buttonStore->buttonPressTime = 0;
    buttonStore->buttonReleaseTime = 0;
    QueueInit(&(buttonStore->buttonQueue));
}
/*!
 * @brief Resets the pressed timer
 * @param buttonStore A pointer to the button struct
 */
static void ButtonPressedEnter(ButtonStore_t* buttonStore)
{
    buttonStore->buttonPressTime = 0;
}
/*!
 * @brief Measures the amount of time the button is pressed. Handles debouncing
 * @param buttonStore A pointer to the button struct
 */
static void ButtonPressedTimer(ButtonStore_t* buttonStore)
{
    buttonStore->buttonPressTime++;

    /* On button release */
    if (buttonStore->ReadButton() != 0)
    {
        /* Actually pressed for a while i.e by a human. Register press on final release */
        if (buttonStore->buttonPressTime >= (BUTTON_PRESS_TIME / INTERVAL_BUTTON_HANDLER))
        {
            ButtonAddEvent(EVENT_BUTTON_PRESSED,
                           buttonStore);
        }

        /* Full release/never pressed */
        ButtonEnterState(buttonStore, EVENT_BUTTON_RELEASED);
    }
    else
    {
        /* Still pressed */
        if ((BUTTON_HELD_TIME / INTERVAL_BUTTON_HANDLER)
                >= (buttonStore->buttonPressTime))
        {
            ButtonEnterState(buttonStore, EVENT_BUTTON_HELD);
        }
    }
}
/*!
 * @brief How to handle the held state start
 * @param buttonStore A pointer to the button struct
 */
static void ButtonHeldEnter(ButtonStore_t* buttonStore)
{
    buttonStore->buttonPressTime = 0;
    buttonStore->buttonNumberOfPresses++;
}
/*!
 * @brief Handling the button continuing to be held
 * @param buttonStore A pointer to the button struct
 */
static void ButtonHeldTimer(ButtonStore_t* buttonStore)
{
    buttonStore->buttonPressTime++;

    if (buttonStore->ReadButton() != 0)
    {
        ButtonAddEvent(EVENT_BUTTON_RELEASED,
                       buttonStore);
        /* Released */
        ButtonEnterState(buttonStore, EVENT_BUTTON_RELEASED);
    }
    else
    {
        /* Still pressed */
        if ((BUTTON_HELD_TIME / INTERVAL_BUTTON_HANDLER)
                >= (buttonStore->buttonPressTime))
        {
            ButtonAddEvent(EVENT_BUTTON_HELD,
                           buttonStore);

            ButtonEnterState(buttonStore, EVENT_BUTTON_HELD);
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
        /* Press detected */
        ButtonEnterState(buttonStore, EVENT_BUTTON_PRESSED);
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
        case EVENT_BUTTON_NULL:
            break;
        case EVENT_BUTTON_RELEASED:
            break;
        case EVENT_BUTTON_PRESSED:
            ButtonPressedEnter(buttonStore);
            break;
        case EVENT_BUTTON_HELD:
            ButtonHeldEnter(buttonStore);
            break;
        case EVENT_BUTTON_DOUBLE_CLICK:
            break;
        case EVENT_BUTTON_DOUBLE_CLICK_HELD:
            break;
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
        case EVENT_BUTTON_NULL:
            break;
        case EVENT_BUTTON_RELEASED:
            ButtonReleaseTimer(buttonStore);
            break;
        case EVENT_BUTTON_PRESSED:
            ButtonPressedTimer(buttonStore);
            break;
        case EVENT_BUTTON_HELD:
            ButtonHeldTimer(buttonStore);
            break;
        case EVENT_BUTTON_DOUBLE_CLICK:
            break;
        case EVENT_BUTTON_DOUBLE_CLICK_HELD:
            break;
        default:
            break;
    }
}
