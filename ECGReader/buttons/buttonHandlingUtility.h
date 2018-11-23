/*!
 * @brief Utility header for the button handling.
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#ifndef __BUTTON_HANDLING_UTILITY_H__
#define __BUTTON_HANDLING_UTILITY_H__

/*!
 * @brief defines all possible states a button can take
 */
typedef enum{
    BUTTON_NULL = 0X00,
    BUTTON_RELEASED = 0X01,
    BUTTON_SEMI_RELEASED = 0X02,
    BUTTON_PRESSED = 0X04,
    BUTTON_HELD  = 0X08,
    BUTTON_DOUBLE_CLICK = 0X10,
    BUTTON_DOUBLE_CLICK_HELD = 0X20,
} BUTTONSTATE_E;

/*!
 * @brief enum for selecting buttons
 */
typedef enum{
    BUTTONS1,
    BUTTONS2
} BUTTONSELECT_T;

#endif /* __BUTTON_HANDLING_UTILITY_H__ */
