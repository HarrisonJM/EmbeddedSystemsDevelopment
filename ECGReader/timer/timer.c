/*!
 * @brief implements the 1ms timer interrupt
 *
 *  Created on: 17 Nov 2015
 *      Author: Len Biro
 */
#include <msp430.h>
#include "buttons/buttonHandler.h"
#include "buttons/buttonHandlingUtility.h"
#include "hardwareAbstractions/I_led.h"

/* Timer variable setup */
int timerAdcReading = 1;
/* Counter */
int msCounter10 = 0;
int msCounter100 = 0;

/*!
 * @brief Inits Timer0
 */
void __TimerInit(void)
{
    TA0CCR0 = 1024; /* Count up to 1024 */
    TA0CCTL0 = 0x10; /* Enable counter interrupts, bit 4=1 */

    TA0CCTL1 = OUTMOD_3;                        // TACCR1 set/reset
    TA0CCR1 = 1023;                             // TACCR1 PWM Duty Cycle
    TA0CTL = TASSEL_2 + MC_1; // Timer A using subsystem master clock, SMCLK(1.1 MHz)
                              // and count UP to create a 1ms interrupt
                              // PWM Period
}

/*!
 * @brief Timer0 A0 1ms interrupt service routine
 *
 * Edits global variable timer::adcReading
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
    msCounter10++;
    msCounter100++;

    if (10 == msCounter10)
    {
        msCounter10 = 0;
        ButtonTimer(BUTTONS1);
        ButtonTimer(BUTTONS2);
    }
}
