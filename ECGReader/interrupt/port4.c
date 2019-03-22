#include <msp430fr5969.h>
#include <buttons/private/O_button.h>
#include <buttons/buttonHandler.h>

#include <leds/LedHandler.h>

#pragma vector=PORT4_VECTOR
__interrupt void port4_ISR(void)
{
    switch(__even_in_range(P4IV,16))
    {
        case 0: break; /* NO INTERRUPT */
        case 2: break; /* P4.0 */
        /* ........ */
        case 12: /* P4.5 */ /* LEFT BUTTON */
            ButtonTimer(BUTTONS1);
//            LEDUse(LED_GREEN, LED_TOGGLE);
            break;
    }
}
