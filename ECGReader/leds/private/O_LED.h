/*!
 * @brief The LED object tracker
 * @author Harrison James Marcks
 * @date 23/11/18
 */
#ifndef __O_LED_H__
#define __O_LED_H__

#include "../LedHandlerUtility.h"

/*!
 * @brief the LED store object
 * This struct is used to track each LEDs state
 * across the same functions, limiting the number of handlers we need
 */
typedef struct LEDSTORE {
    /*!{*/
    LEDSTATE_T state; /*! < The current state of the led */
    int period; /*! < The LEDs current period (for counting against the timer) */
    void (*LEDOn)(); /*! < Function pointer for turning on the LED */
    void (*LEDOff)(); /*! < Function pointer for turning off the LED */
    void (*LEDToggle)(); /*! < Function pointer for toggling the LED */
    /*!}*/
} LEDSTORE_T;

void LEDGreenInit(LEDSTORE_T* green);
void LEDRedInit(LEDSTORE_T* red);

#endif /* __O_LED_H__ */
