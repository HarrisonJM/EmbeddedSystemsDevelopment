/*!
 * @brief Utility header for the button handling.
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#ifndef __BUTTON_HANDLING_UTILITY_H__
#define __BUTTON_HANDLING_UTILITY_H__

#define INTERVAL_BUTTON_HANDLER 10
#define MINIMUM_BUTTON_INTERACTION_TIME 100
#define BUTTON_HELD_TIME 200
#define DOUBLE_CLICK_COUNTER 50

typedef enum{
    BUTTON_NULL,
    BUTTON_RELEASED,
    BUTTON_PRESSED,
    BUTTON_HELD,
    BUTTON_DOUBLE_CLICK,
    BUTTON_DOUBLE_CLICK_HELD
} BUTTONSTATE_E;

typedef enum{
    BUTTONS1,
    BUTTONS2
} BUTTONSELECT_T;

#endif /* __BUTTON_HANDLING_UTILITY_H__ */
