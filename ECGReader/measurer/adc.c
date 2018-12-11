/*!
 * @brief Driving the analogue to digital Converter (ADC)
 * @author Dan Steer & Len Biro
 * @date 10/12/2018
 */

#include <msp430.h>
#include "measurer/adc.h"

volatile int rdg = 0;
int rdgsArray[RDGSARRAYSIZE] = {0};
unsigned int rdgsIndex = 0;

/*!
 * @brief Setting up the board GPIO for the ADC
 */
void ADCInitHardware(void)
{
  P1OUT &= ~BIT0; /*Clear LED to start*/
  P1DIR |= BIT0; /*Set P1.0/LED to output*/

  P4DIR |= BIT3;
  P4REN |= BIT3;
  P4OUT |= BIT3;
  P4DIR = 0xFF ^ BIT3;

  P3DIR |= BIT0;
  P3REN &= ~BIT0;
  P3OUT |= BIT0;
  P3DIR &= (0xFF ^ BIT0);

  P3SEL1 |= BIT1; /*Configure P3.0 for ADC*/
  P3SEL0 |= BIT1;

  /* Configure ADC12*/
  ADC12CTL0 = ADC12SHT0_2 | ADC12ON; /*Sampling time, S&H=16, ADC12 on*/
  /*ADC12CTL1 = ADC12SHP;*/ /* Use sampling timer*/
  /*Use TA0.1 to trigger, and repeated-single-channel*/
  ADC12CTL1 = ADC12SHP | ADC12SHS_1 | ADC12CONSEQ_2;
  ADC12CTL2 |= ADC12RES_2; /*12-bit conversion results*/
  ADC12CTL3 |= 0x0C;
  ADC12MCTL12 = ADC12INCH_12; /*A12 ADC input select; Vref=AVCC*/
  ADC12IER0 |= ADC12IE12; /*Enable ADC conv complete interrupt*/  
}

/*!
 * @brief Wait and start the A to D conversion. 
 */
void ADCStart(void)
{
    __delay_cycles(5000); /*Wait 5000 clock cycles*/
  /*ADC12CTL0 how to configure coversions | ADC12ENC enable conversions | ADC12SC start conversion*/
    ADC12CTL0 |= ADC12ENC | ADC12SC; /*Start sampling/conversion*/

    //__bis_SR_register(LPM0_bits | GIE); /*LPM0, ADC12_ISR will force exit*/
    //__no_operation(); /*For debugger*/  
}


