/*!
 * @brief Utility header for the button handling.
 * @author Harrison J Marcks
 * @addtogroup buttons
 * @date 12/11/2018
 */

#ifndef __BUTTON_HANDLING_UTILITY_H__
#define __BUTTON_HANDLING_UTILITY_H__

/*!
 * @brief defines all possible states a button can take
 */
typedef enum{
    EVENT_BUTTON_NULL = 0X00,
    EVENT_BUTTON_RELEASED = 0X01,
    EVENT_BUTTON_SEMI_RELEASED = 0X02,
    EVENT_BUTTON_PRESSED = 0X04,
    EVENT_BUTTON_HELD  = 0X08,
    EVENT_BUTTON_DOUBLE_CLICK = 0X10,
    EVENT_BUTTON_DOUBLE_CLICK_HELD = 0X20
} BUTTONSTATE_E;

/*!
 * @brief enum for selecting buttons
 */
typedef enum{
    BUTTONS1,
    BUTTONS2
} BUTTONSELECT_T;

#endif /* __BUTTON_HANDLING_UTILITY_H__ */
