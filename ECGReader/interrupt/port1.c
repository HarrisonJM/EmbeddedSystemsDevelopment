#include <msp430fr5969.h>
#include <buttons/private/O_button.h>
#include <buttons/buttonHandler.h>

#include <leds/LedHandler.h>

#pragma vector=PORT1_VECTOR
__interrupt void port1_ISR(void)
{
    switch(__even_in_range(P1IV,16))
    {
        case 0: break; /* NO INTERRUPT */
        case 2:  /* P1.0 */ /* RIGHT BUTTON */
//            ButtonTimer(BUTTONS2);
            break;
        case 4:
            LEDUse(LED_GREEN, LED_TOGGLE);
            break;
        /* ........ */
        case 12: /* P1.5 */
            break;
    }
}
