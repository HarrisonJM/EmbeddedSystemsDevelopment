/*!
 * @brief Utility header for the button handling.
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#ifndef __BUTTON_HANDLING_UTILITY_H__
#define __BUTTON_HANDLING_UTILITY_H__

typedef enum{
    BUTTON_NULL,
    BUTTON_RELEASED,
    BUTTON_SEMI_RELEASED,
    BUTTON_PRESSED,
    BUTTON_HELD,
    BUTTON_DOUBLE_CLICK,
    BUTTON_DOUBLE_CLICK_HELD,
} BUTTONSTATE_E;

typedef enum{
    BUTTONS1,
    BUTTONS2
} BUTTONSELECT_T;

#endif /* __BUTTON_HANDLING_UTILITY_H__ */
