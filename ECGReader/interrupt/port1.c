/* RIGHT BUTTON */

#include <msp430fr5969.h>

#pragma vector=PORT1_VECTOR
__interrupt void port1_ISR(void)
{
    switch(P1IV)
    {
        case 0:
            // Button pressed
            break;
    }
}