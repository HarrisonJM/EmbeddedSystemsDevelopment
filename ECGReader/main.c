/*!
 * @brief defines the main entry point for the program
 * @date 10/12/2018
 */

#include <msp430.h>

#include "helpers/boollint.h"

#include "buttons/buttonHandler.h"
#include "buttons/buttonHandlingUtility.h"
#include "hardwareAbstractions/public/I_button.h"

#include "hardwareAbstractions/public/I_led.h"

#include "hardwareAbstractions/public/I_lcd.h"
#include "screen/handler/screenHandler.h"

#include "menu/activities/ECG/activityECG.h"

//#include "measurer/adc.h"

#include "string.h"
#include "stdio.h"
unsigned int ADC_value=0, ADC_value2=0;
#define RDGSARRAYSIZE 192
volatile int rdg = 0;
int rdgsArray [RDGSARRAYSIZE];
unsigned int rdgsIndex = 0;
bool invert = true; 

    #if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
    #pragma vector = ADC12_VECTOR
    __interrupt void ADC12_ISR(void)
    #elif defined(__GNUC__)
    void __attribute__ ((interrupt(ADC12_VECTOR))) ADC12_ISR (void)
    #else
    #error Compiler not supported!
    #endif
    {
     switch (__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG))
     {
     case ADC12IV_ADC12IFG1: // ADC12MEM1 Interrupt
        //ADC_value = ADC12MEM0; // Save MEM0
        ADC_value2 = ADC12MEM0; // Save MEM1
        //ADC_value2 = ADC12MEM1; // Save MEM1
        rdg = rdgsArray[rdgsIndex++] = ADC12MEM12;
       // rdg = rdgsArray[rdgsIndex++] = ADC12MEM0;
        if (rdgsIndex >= RDGSARRAYSIZE) rdgsIndex = 0;
        
      //  ScreenPrintCustom(DisplayBuffer, "Hello 3", invert);
       // ScreenFlushDisplayBuffer();
     __bic_SR_register_on_exit(LPM0_bits | GIE); // Exit CPU, clear interrupts
     break;
     default: break;
     }
    }















EVENTQUEUE_T* buttonS1Queue;
EVENTQUEUE_T* buttonS2Queue;








int main(void)
{
    int i;
for (i = 0; i< RDGSARRAYSIZE; i++) {
    rdgsArray[i] = 0;
}

    /*! @todo move into an init function */
    /*!@{*/
    /*! @brief Stop watchdog timer */
    WDTCTL = WDTPW | WDTHOLD;
    /*!
     * @brief Disable the GPIO power-on default high-impedance mode
     * changing/removing this means that all pins must be set manually (including unused ones. Perhaps it helps with re-flashing?
     */
    PM5CTL0 &= ~LOCKLPM5;
    /*! @brief enable interrupts */
     _BIS_SR (GIE);
    /*!@}*/

    /* Setup button related things */
//    __ButtonHardwareinit();
//    ButtonInitHandlerBothButtons();
//    buttonS1Queue = ButtonGetQueue(BUTTONS1);
//    buttonS2Queue = ButtonGetQueue(BUTTONS2);

    /* Setup LED stuff*/
//    
    /* Timers and interrupts */
   // __LEDHardwareInit();

    // ADC Vector function adapted from http://www.ti.com/lit/zip/slac536
    // using MSP430FR59xx_adc12_01.c
    // Written by: T. Witt / P. Thanigai, Texas Instruments Inc., November 2013



    
    /* Display stuff*/
    LCDInitHardware();
   // ScreenDisplayBufferInit(' ');
    ScreenPrintCustom(DisplayBuffer, "Hello World", invert);
    ScreenFlushDisplayBuffer();
    




  /*P4DIR |= BIT3;
  P4REN |= BIT3;
  P4OUT |= BIT3;
  P4DIR = 0xFF ^ BIT3;

  P3DIR |= BIT0;
  P3REN &= ~BIT0;
  P3OUT |= BIT0;
  P3DIR &= (0xFF ^ BIT0);

  P3SEL1 |= BIT1; /*Configure P3.0 for ADC*/
  //P3SEL0 |= BIT1;

  /* Configure ADC12
    ADC12CTL0 = ADC12SHT0_2 | ADC12ON; /*Sampling time, S&H=16, ADC12 on*/
    /*ADC12CTL1 = ADC12SHP;*/ /* Use sampling timer*/
    /*Use TA0.1 to trigger, and repeated-single-channel
    ADC12CTL1 = ADC12SHP | ADC12SHS_1 | ADC12CONSEQ_2;
    ADC12CTL2 |= ADC12RES_2; /*12-bit conversion results
    ADC12CTL3 |= 0x0C;
    ADC12MCTL12 = ADC12INCH_12; /*A12 ADC input select; Vref=AVCC
    ADC12IER0 |= ADC12IE12; /*Enable ADC conv complete interrupt  */

    // Using PIN3 for ADC
    P3SEL1 |= BIT1;
    P3SEL0 |= BIT1;

    // Configure the ADC
   // ADC12CTL0 = ADC12SHT0_2 | ADC12ON; // Cycle Sample Time, ADC On
   // ADC12CTL1 = ADC12SHP; // Source clock is sample timer
  //  ADC12CTL2 |= ADC12RES_2; // 12-bit conversion
    //ADC12IER0 |= ADC12IE0; // interrupt MEM0
  //  ADC12IER0 |= ADC12IE12; // Enable ADC conv complete interrupt
    //USEFUL SHIT: interrupt is set to trigger on only the flag of memory register 1 
 //   ADC12MCTL0 |= ADC12INCH_4 | ADC12VRSEL_3; // Select A4, Vref = 2.5V

    // ENABLE AND START CONVERSIONS BITCH
//    ADC12CTL0 |= ADC12ENC | ADC12SC; // Sampling and conversion start
  //   __bis_SR_register(LPM0_bits + GIE); // LPM0, ADC12_ISR will force exit
   //  __no_operation();

     /* USEFUL SHIT
    The__bis_SR_register() command enables the low power mode in the status register after returning
    from the ADC interrupt routine, and enables the general interrupt to wake up the MSP430 upon another
    ADC sampling. 
     */

// Configure ADC12
 // Turn on ADC and enable multiple conversions
 //ADC12CTL0 = ADC12SHT0_2 | ADC12ON | ADC12MSC;
 ADC12CTL0 = ADC12SHT0_2 | ADC12ON; 
 // Sampling timer, single sequence
 ADC12CTL1 |= ADC12SHP | ADC12CONSEQ_1;
 // 12-bit conversion
 ADC12CTL2 |= ADC12RES_2;
 // Enable ADC interrupt on MEM1
 ADC12IER0 |= ADC12IE1;
 // A3 select, Vref=1.2V
 //ADC12MCTL0 |= ADC12INCH_3 | ADC12VRSEL_1;
 // A4 select, Vref=1.2V, End of Sequence
 //ADC12MCTL1 |= ADC12INCH_4 | ADC12VRSEL_1 | ADC12EOS;
    //ADC12MCTL12 = ADC12INCH_12;  
/*

   ADC12CTL0 = ADC12SHT0_2 | ADC12ON;        // Sampling time, S&H=16, ADC12 on
  //ADC12CTL1 = ADC12SHP;                     // Use sampling timer
  // Use TA0.1 to trigger, and repeated-single-channel
  ADC12CTL1 = ADC12SHP | ADC12SHS_1 | ADC12CONSEQ_2;
  ADC12CTL2 |= ADC12RES_2;                  // 12-bit conversion results
  ADC12CTL3 |= 0x0C;
  ADC12MCTL12 = ADC12INCH_12;                // A12 ADC input select; Vref=AVCC // SELECT INPUT CHAN
  ADC12IER0 |= ADC12IE12;                    // Enable ADC conv complete interrupt
*/

    char adcRdg [5];



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
        sprintf (adcRdg, "%d", ADC_value2);
        
        ScreenPrintCustom(DisplayBuffer, adcRdg, invert);
        ScreenFlushDisplayBuffer();
       
    }
}




