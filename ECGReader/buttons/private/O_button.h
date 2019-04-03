/*!
 * @brief Button Object header
 * @author Harrison J Marcks
 * @addtogroup buttons
 * @{
 * @addtogroup private
 * @{
 * @date 12/11/2018
 */

#ifndef __O_BUTTON_H__
#define __O_BUTTON_H__

#include "../../helpers/boollint.h"
#include "../buttonHandlingUtility.h"
#include "../../helpers/eventQueue/eventQueue.h"

/*!
 * @brief the button store object
 * This struct is used to track each button's state
 * across the same functions, limiting the number of handlers we need
 */
typedef struct Button
{
    /*!@{*/
    int buttonNumberOfPresses;  /*! < The number of times the button has been pressed (deprecated)*/
    BUTTONSTATE_E buttonState;  /*! < The current state of the button */
    int buttonPressTime;        /*! < The Amount of time the button has been pressed for */
    int buttonReleaseTime;      /*! < The amount of time the button has been released for*/
    bool (*ReadButton)(void);   /*! < A function pointer to the relevant button check */
    EVENTQUEUE_T buttonQueue;   /*! < The queue to read the button from */
    /*!@}*/
} ButtonStore_t;

void ButtonS1Init(ButtonStore_t* S1);
void ButtonS2Init(ButtonStore_t* S2);

#endif /* __O_BUTTON_H__ */

/*! @} @} */
