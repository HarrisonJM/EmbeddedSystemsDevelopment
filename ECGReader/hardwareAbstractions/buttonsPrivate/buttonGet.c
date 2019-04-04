/*!
 * @brief Non-hardware agnostic implementation for grabbing button information
 * @author Harrison J Marcks
 * @addtogroup hardwareAbstractions
 * @{
 * @addtogroup buttonsPrivate
 * @{
 * @date 8 Nov 2018
 * @{
 */
#include <msp430fr5969.h>

#include "helpers/boollint.h"
/*!
 * @brief Initialises the button hardware
 */
void __ButtonHardwareinit()
{
    /* Button S2 */
    P1DIR &= ~BIT1; /* P1.1 input (switch 2) */
    P1REN |= BIT1; /* P1.1 pull up resistor */

    /* Button S1*/
    P4DIR &= ~BIT5; /* P4.5 input (switch 1) 0b0010 0000*/
    P4REN |= BIT5; /* P4.5 pull up resistor */
}
/*!
 * @brief hardware implementation for reading button S2 (right)
 * @return 1 for no press detected, otherwise 0
 */
bool __ReadButtonS2()
{
    return (P1IN & BIT5);
}
/*!
 * @brief Hardware implementation for reading Button S1 (left)
 * @return 1 for no press detected, otherwise 0
 */
bool __ReadButtonS1()
{
    return (P4IN & BIT5);
}

/*! @} @} @} */