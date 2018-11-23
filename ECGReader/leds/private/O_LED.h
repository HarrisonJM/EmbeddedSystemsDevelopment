/*!
 * @brief The LED object tracker
 * @author Harrison James Marcks
 * @date 23/11/18
 */
#ifndef __O_LED_H__
#define __O_LED_H__

#include "../LedHandlerUtility.h"

typedef struct LEDSTORE {
    LEDSTATE_T state;
    int period;
    void (*LEDOn)();
    void (*LEDOff)();
    void (*LEDToggle)();
} LEDSTORE_T;

void LEDGreenInit(LEDSTORE_T* green);
void LEDRedInit(LEDSTORE_T* red);

#endif /* __O_LED_H__ */
