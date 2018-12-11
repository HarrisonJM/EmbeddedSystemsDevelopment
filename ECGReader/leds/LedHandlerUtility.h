/*!
 * @brief Utility header for the LED Handler
 * @author Harrison Marcks
 * @date 11/12/2018
 */
#ifndef __LEDHANDLERUTILITY_H__
#define __LEDHANDLERUTILITY_H__

/*! @brief Defines each possible action state an LED can take */
typedef enum {
    /*!@{*/
    LED_NULL = 0x00,    /* < Null state */
    LED_ON = 0x01,      /* < LED is on/turn on the LED */
    LED_OFF = 0x02,     /* < LED is off/turn off the LED */
    LED_TOGGLE = 0x04   /* < Toggle the LED into the other state */
    /*!@}*/
} LEDACTION_T;

/*! @brief The two LEDs we have*/
typedef enum {
    LED_GREEN,
    LED_RED
} LEDSELECT_T;

#endif /* __LEDHANDLERUTILITY_H__ */
