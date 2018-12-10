/*!
 * @brief contains only the timer init functions
 * @author Harrison Marcks
 * @date 10/12/18
 */

#include <msp430.h>

/*!
 * @brief Inits Timer0(1ms)
 */
void InterruptTimerA0Init(void)
{
    TA0CCR0 = 1024; /* Count up to 1024 */
    TA0CCTL0 = 0x10; /* Enable counter interrupts, bit 4=1 (5th bit = 1) */

    TA0CCTL1 = OUTMOD_3;                        // TACCR1 set/reset
    TA0CCR1 = 1023;                             // TACCR1 PWM Duty Cycle
    TA0CTL = TASSEL_2 + MC_1; // Timer A using subsystem master clock, SMCLK(1.1 MHz)
                              // and count UP to create a 1ms interrupt
                              // PWM Period
}
/*!
 * @brief Inits the TimerA2 for capture
 * @todo sort out sliders what with the capture
 */
void InterruptTimerA2Init(void)
{
    /* Timer A2 used for capture */
   TA2CTL |= TACLR;
   TA2CTL   = ID_3 + TBSSEL_2 + MC_2;  /* Timer A2 using subsystem master clock, SMCLK(1.1 MHz) */
   TA2CCTL1 = CM_1+CCIS_0+CAP+SCS;     /* Capture set up for Timer A2 */
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
