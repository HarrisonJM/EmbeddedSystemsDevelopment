/*
 * timer.c
 *
 *  Created on: 17 Nov 2015
 *      Author: Len Biro
 */
#include <msp430.h>

/* Timer variable setup */
int timerAdcReading = 1;

/*!
 * @breif inits Timer0
 */
void initTimer(void)
{
    P4DIR &= ~0x40;                             /*p4.6*/
    P4REN |= 0x40;                              /* Set P1.1 pull-up resistor enabled */
    P4OUT |= 0x40;
    P4DIR |= 0x40;                              /* Set P4.6 to output direction */

    TA0CCR0 = 1023;                             /* Count up to 1024 */
    TA0CCTL0 = 0x10;                            /* Enable counter interrupts, bit 4=1 */
    TA0CCTL1 = OUTMOD_3;                        // TACCR1 set/reset
    TA0CCR1 = 1023;                             // TACCR1 PWM Duty Cycle
    TA0CTL = TASSEL_2 + MC_1;                   // Timer A using subsystem master clock, SMCLK(1.1 MHz)
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
	//Time to take a reading
    static int heartbeat = 1;
	timerAdcReading++;

	if (timerAdcReading >= 40)
	{
	    timerAdcReading = 1;
	}

	// Toggle the red LED 500ms on and 500ms off
	heartbeat++;
	if (heartbeat >= 500) {
		heartbeat = 1;
		P4OUT ^= 0x40;
	}
}
