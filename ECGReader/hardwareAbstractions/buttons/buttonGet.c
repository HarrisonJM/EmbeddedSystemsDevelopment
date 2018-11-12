/*!
 * @brief Non-hardware agnostic implementation for grabbing button information
 * @author Harrison J Marcks
 * @date 8 Nov 2018
 */
#include <msp430.h>

#include "buttonGet.h"

/*!
 * @brief Initialises the button hardware
 */
int __initButtonHardware()
{
    P1DIR &= ~0x02; // P1.1 input (switch 2)
    P1REN |= 0x02; // P1.1 pull up resistor

    P4DIR &= ~0x04; /* P4.6 input (switch 1) */
    P4REN |= 0x02; /* P4.6 pull up resistor */
}

/*!
 * @brief hardware implementation for reading button S2 (right)
 * @return 1 for no press detected, otherwise 0
 */
int __ReadButtonS2()
{
    return (P1IN & 0x02);
}

/*!
 * @brief Hardware implementation for reading Button S1 (left)
 * @return 1 for no press detected, otherwise 0
 */
int __ReadButtonS1()
{
    return (P4IN & 0x02);
}
