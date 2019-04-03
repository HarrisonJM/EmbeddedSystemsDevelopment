/*!
 * @brief defines the main entry point for the program
 * @date 10/12/2018
 */

#include <msp430fr5969.h>

#include "postPowerOn/POST.h"

#include "helpers/eventQueue/eventQueue.h"

#include "menu/activities/activites.h"

#include <screen/handler/screenHandler.h>

#include "leds/LedHandler.h"
#include "leds/LedHandlerUtility.h"

/* PROTOTYPES */
void main(void);

void main(void)
{
    /* Perform the post */
    POST();

    ScreenPrint("POST Success",' ');
    while(1)
    {
        ScreenSplash();
    }
}
