/*!
 * @brief port =s 1 and 2 interrupt initialisations
 * @author harrison Marcks
 * @addtogroup hardwareAbstractions
 * @{
 * @addtogroup portsPrivate
 * @{
 * @date 3 Apr 2019
 */
#include <msp430fr5969.h>

void InterruptPort1Init()
{
    P1SEL1 &= (~BIT1);  /* Set P1.1 SEL as GPIO */
    P1DIR &= (~BIT1);   /* Set P1.1 SEL as Input */
    P1IES |= (BIT1);    /* Falling Edge */
    P1IFG &= (~BIT1);   /* Clear interrupt flag for P1.1 */
    P1IE |= (BIT1);     /* Enable interrupt for P1.1 */
}

void InterruptPort4Init()
{
    P4SEL1 &= (~BIT5);  /* Set P1.3 SEL as GPIO */
    P4DIR &= (~BIT5);   /* Set P1.3 SEL as Input */
    P4IES |= (BIT5);    /* Falling Edge */
    P4IFG &= (~BIT5);   /* Clear interrupt flag for P1.3 */
    P4IE |= (BIT5);     /* Enable interrupt for P1.3 */
}
