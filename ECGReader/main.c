/*!
 * @brief defines the main entry point for the program
 * @date 10/12/2018
 */

#include <msp430.h>

#include "helpers/boollint.h"

//#include "buttons/buttonHandler.h"
//#include "buttons/buttonHandlingUtility.h"
//#include "hardwareAbstractions/public/I_button.h"

//#include "hardwareAbstractions/public/I_led.h"

//#include "hardwareAbstractions/public/I_lcd.h"
#include "screen/handler/screenHandler.h"

//#include "menu/activities/ECG/activityECG.h"

//#include "measurer/adc.h"

#include "string.h"
#include "stdio.h"
/*unsigned int ADC_value=0, ADC_value2=0;
#define RDGSARRAYSIZE 192
volatile int rdg = 0;
int rdgsArray [RDGSARRAYSIZE];
unsigned int rdgsIndex = 0;*/
bool invert = true; 
/*
  
    #pragma vector = ADC12_VECTOR
    __interrupt void ADC12_ISR(void)
    {
     switch (__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG)) {
        case ADC12IV_ADC12IFG12:  //break;        // Vector 36:  ADC12MEM12
        /*rdg = rdgsArray[rdgsIndex++] = ADC12MEM12;
        if (rdgsIndex >= RDGSARRAYSIZE) rdgsIndex = 0;
        __bic_SR_register_on_exit(LPM0_bits); // Exit active CPU*/
    //..    ADC_value = ADC12MEM12;
      //break;
/*
     case ADC12IV_ADC12IFG1: // ADC12MEM1 Interrupt
        //ADC_value = ADC12MEM0; // Save MEM0
        //ADC_value2 = ADC12MEM0; // Save MEM1
        //ADC_value2 = ADC12MEM1; // Save MEM1
        rdg = rdgsArray[rdgsIndex++] = ADC12MEM12;
       // rdg = rdgsArray[rdgsIndex++] = ADC12MEM0;
        if (rdgsIndex >= RDGSARRAYSIZE) rdgsIndex = 0;
        
      //  ScreenPrintCustom(DisplayBuffer, "Hello 3", invert);
       // ScreenFlushDisplayBuffer();
     __bic_SR_register_on_exit(LPM0_bits | GIE); // Exit CPU, clear interrupts
     break;*/
     //default: break;
    // }
    //}



unsigned int DMA_DST[1024] = { 0 };

int main(void) {
  unsigned int * pDMA_DST = (unsigned int *) DMA_DST;
  unsigned int i;

  //Initialising with something obvious to test DMA.
  for (i = 0; i < 64; i++)
    *pDMA_DST++ = '*';

    pDMA_DST = (unsigned int *) DMA_DST;

    /*! @todo move into an init function */
    /*!@{*/
    /*! @brief Stop watchdog timer */
    WDTCTL = WDTPW | WDTHOLD;
    /*!
     * @brief Disable the GPIO power-on default high-impedance mode
     * changing/removing this means that all pins must be set manually (including unused ones. Perhaps it helps with re-flashing?
     */
      
      // GPIO Setup
    P1OUT &= ~BIT0;                           // Clear LED to start
    P1DIR |= BIT0;                            // Set P1.0/LED to output

    P4DIR |= BIT3;
    P4REN |= BIT3;
    P4OUT |= BIT3;
    P4DIR = 0xFF ^ BIT3;

    P3DIR |= BIT0;
    P3REN &= ~BIT0;
    P3OUT |= BIT0;
    P3DIR = 0xFF ^ BIT0;

    P3SEL1 |= BIT1;                           // Configure P3.0 for ADC
    P3SEL0 |= BIT1;

    PM5CTL0 &= ~LOCKLPM5;
    /*! @brief enable interrupts */
 //    _BIS_SR (GIE);
 

    //initTimer
  TA0CCR0 = 1100; // Count
  TA0CCTL1 = OUTMOD_3;                      // TACCR1 set/reset
  TA0CCR1 = 1100;                           // TACCR1 PWM Duty Cycle
  TA0CTL = TASSEL_2 + MC_1 + TACLR; // Timer A using subsystem master clock, SMCLK(1.1 MHz)
  // and count UP to create a ~1ms interrupt flag
  // PWM Period
// Configure ADC12 Sampling time, S&H=16, ADC12 on
  ADC12CTL0 = ADC12SHT0_2 | ADC12ON;
  // Use TA0.1 to trigger, and repeated-single-channel
  ADC12CTL1 = ADC12SHP | ADC12SHS_1 | ADC12CONSEQ_2;
  // 12-bit conversion results and store in memory register 12
  ADC12CTL2 |= ADC12RES_2;
  ADC12CTL3 |= 0x0C;
  // A12 ADC input select; Vref=AVCC
  ADC12MCTL12 = ADC12INCH_12;
  // Enable ADC conv complete interrupt.
//  ADC12IER0 |= ADC12IE12;

  // Setup DMA1
  DMACTL0 = DMA1TSEL_26;  // ADC12IFGx triggered
  DMACTL4 = DMARMWDIS;  // Read-modify-write disable
  DMA1CTL &= ~DMAIFG;   //Clear action flag.
  DMA1CTL = DMADT_4 + DMADSTINCR_3 + DMASRCINCR_0;// Rpt single tranfer, inc dst.
  //Total size of transfer region.
  DMA1SZ = 50;

  __data16_write_addr((unsigned short) &DMA1SA, (unsigned long) &ADC12MEM12);

  __data16_write_addr((unsigned short) &DMA1DA, (unsigned long) DMA_DST);

  DMA1CTL |= DMAREQ;
  __delay_cycles(5000);

  ADC12CTL0 |= ADC12ENC;        // Start sampling/conversion

  DMA1CTL |= (DMAEN );//|DMAIE); //Enable DMA interrupt if you want to debug DMA

  __bis_SR_register(/*LPM0_bits |*/GIE);    // LPM0, ADC12_ISR will force exit

 
    /* Display stuff*/
    LCDInitHardware();
   // ScreenDisplayBufferInit(' ');
    ScreenPrintCustom(DisplayBuffer, "Hello World", invert);
    ScreenFlushDisplayBuffer();



  while (1) {
    __no_operation();                       // For debugger
  }


   

   /* char adcRdg [5];



    char blah[10] = "blah";

    while(1) {
        ScreenPrintCustom(DisplayBuffer, "          ", invert);
        ScreenFlushDisplayBuffer();
        __delay_cycles(5000);
        ADC12CTL0 |= ADC12ENC | ADC12SC; // Sampling and conversion start
        __bis_SR_register(LPM0_bits + GIE); // LPM0, ADC12_ISR will force exit.
       // ScreenPrintCustom(DisplayBuffer, " ", invert);
        //
       // ScreenFlushDisplayBuffer();
        //sprintf(adcRdg, "%d", ADC_value);
        sprintf (adcRdg, "%d", ADC_value);
        
        ScreenPrintCustom(DisplayBuffer, adcRdg, invert);
        ScreenFlushDisplayBuffer();
       
    }*/
}




