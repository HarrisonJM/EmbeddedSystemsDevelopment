/*!
 * @brief Non-hardware agnostic implementation for grabbing button information
 * @author Harrison J Marcks
 * @date 8 Nov 2018
 */
#include <hardwareAbstractions/buttonsPrivate/buttonGet.h>
#include <msp430.h>

/*!
 * @brief Initialises the button hardware
 */
void __initButtonHardware()
{
    /* Button S2 */
    P1DIR &= ~0x02; // P1.1 input (switch 2)
    P1REN |= 0x02; // P1.1 pull up resistor

    /* Button S1 WIP */
    P4DIR &= ~0x20; /* P4.5 input (switch 1) 0b0010 0000*/
    P4REN |= 0x20; /* P4.5 pull up resistor */
}
/*!
 * @brief hardware implementation for reading button S2 (right)
 * @return 1 for no press detected, otherwise 0
 */
inline bool __ReadButtonS2()
{
    return (P1IN & 0x02);
}
/*!
 * @brief Hardware implementation for reading Button S1 (left)
 * @return 1 for no press detected, otherwise 0
 */
bool __ReadButtonS1()
{
    return (P4IN & 0x02);
}
