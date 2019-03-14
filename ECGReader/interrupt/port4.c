/* LEFT BUTTON */

#include <msp430fr5969.h>
#include <buttons/private/O_button.h>

#pragma vector=PORT4_VECTOR
__interrupt void port4_ISR(void)
{
    switch(__even_in_range(P4IV,16))
    {
        case 0: break; /* NO INTERRUPT */
        case 2: break; /* P4.0 */
        /* ........ */
        case 12: /* P4.5 */
            ButtonTimer(BUTTONS1);
            break;
    }
}