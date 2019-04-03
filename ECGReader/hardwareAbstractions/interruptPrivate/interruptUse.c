/*!
 * @brief contains only the timer init functions
 * @author Harrison Marcks
 * @addtogroup hardwareAbstractions
 * @{
 * @addtogroup interruptPrivate
 * @{
 * @date 10/12/18
 */

#include <msp430fr5969.h>

#define ACCUMULATION_CYCLES 1000

/*!
 * @brief Inits Timer0(1ms)
 */
void InterruptTimerA0Init(void)
{
    TA0CCR0 = 1024; /* Count up to 1024 */
    TA0CCTL0 = 0x10; /* Enable counter interrupts, bit 4=1 (5th bit = 1) */

    TA0CCTL1 = OUTMOD_3;                        /* TACCR1 set/reset */
    TA0CCR1 = 1024;                             /* TACCR1 PWM Duty Cycle */
    TA0CTL = TASSEL_2 + MC_1 + TACLR; /* Timer A using subsystem master clock, SMCLK(1.1 MHz)
                                         and count UP to create a 1ms interrupt
                                         PWM Period */
}
/*!
 * @brief Inits the TimerA2 for capture
 * @todo sort out sliders what with the capture
 */
void InterruptTimerA2Init(void)
{
    /* Timer A2 used for capture */
   TA2CTL |= TACLR;
   /* TA2 set as timer with RO as clock and TA3 as gated enable. CCIS is
   toggled between gnd and vcc. */
   TA2CTL = TASSEL_3 + MC_2;

   /*TA3 set as gate.*/
   TA3CCR0 = ACCUMULATION_CYCLES;
   TA3CTL = TASSEL_2 + MC_1;
   TA3CCTL0 = CCIE;
}
/*!
 * @brief initialises the UCB0 interrupt for use
 */
void InterruptUCB0Init(void)
{
/*
    P4SEL1 &= (~BIT5); // Set P1.3 SEL as GPIO
    P4DIR &= (~BIT5); // Set P1.3 SEL as Input
    P4IES |= (BIT5); // Falling Edge
    P4IFG &= (~BIT5); // Clear interrupt flag for P1.3
    P4IE |= (BIT5); // Enable interrupt for P1.3
*/
}
/*!
 * @brief Disables Interrupts
 */
void InterruptDisable(void)
{
    _BIC_SR(GIE);
}
/*!
 * @brief Enables Interrupts
 */
void InterruptEnable(void)
{
    _BIS_SR(GIE);
}

/*! @} @} */
