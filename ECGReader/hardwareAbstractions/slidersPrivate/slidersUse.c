/*!
 * @brief Sliders initialization
 * @author Harrison Marcks
 * @addtogroup hardwareAbstractions
 * @addtogroup slidersPrivate
 * @date 10/12/2018
 */

#include <msp430.h>
/*!
 * @brief initialises the slider hardware
 */
void SliderHardwareInit(void)
{
    /* Capacitive Touch */
    CAPTIO0CTL = CAPTIOEN + (3<<4) + (4<<1);

    /* Right slider */
    P1REN  |= BIT3;     /* Pull up resistor */
    P1DIR  |= BIT3;     /* activiate */
    P1OUT  &= ~BIT3;    /* input */

    P1REN  |= BIT4;
    P1DIR  |= BIT4;
    P1OUT  &= ~BIT4;

    P1REN  |= BIT5;
    P1DIR  |= BIT5;
    P1OUT  &= ~BIT5;

    /* Left Slider */
    P3REN  |= BIT4;
    P3DIR  |= BIT4;
    P3OUT  &= ~BIT4;

    P3REN  |= BIT5;
    P3DIR  |= BIT5;
    P3OUT  &= ~BIT5;

    P3REN  |= BIT6;
    P3DIR  |= BIT6;
    P3OUT  &= ~BIT6;
}
