/*!
 * @brief Initlisation and configuration for the ADC
 * @author Dan Steer
 * @date 11/03/2019
 */

#include <msp430.h>

/* Local function prototypes */
static void ADCInitHardware(void);
static void ADCConfig(void);
static void ADCDMAConfigure(void);
/* ... */

/*!
 * @brief Call neccessary functions to setup the ADC
 */
void ADCSetup()
{
	ADCInitHardware();
	ADCConfig();
	ADCDMAConfigure();
}

/*!
 * @brief Initialise hardware being used for ADC
 */
static void ADCInitHardware()
{
	P3DIR |= BIT0;
	P3REN &= ~BIT0;
	P3OUT |= BIT0;
	P3DIR = 0xFF ^ BIT0;
	P3SEL1 |= BIT1;
	P3SEL0 |= BIT1;
}

/*!
 * @brief Configure ADC registers
 */
static void ADCConfig() 
{
	// Configure ADC12 Sampling time, S&H=16, ADC12 on
	ADC12CTL0 = ADC12SHT0_2 | ADC12ON; // reg 0 = smple tim 2 | turn on ADC
	// Use TA0.1 to trigger, and repeated-single-channel
	ADC12CTL1 = ADC12SHP | ADC12SHS_1 | ADC12CONSEQ_2; // reg 1 = smpl & hld pls md sel | tim val | conv seq mode
	// 12-bit conversion results and store in memory register 12
	ADC12CTL2 |= ADC12RES_2; // reg 2 = set result res to 12bit
	ADC12CTL3 |= 0x0C; // reg 3 = something internal maybe, wtf -_-
	// A12 ADC input select; Vref=AVCC
	ADC12MCTL12 = ADC12INCH_12; // reg 12 = input channel 12
	// Enable ADC conv complete interrupt.
	//	ADC12IER0 |= ADC12IE12;
}

/*!
 * @brief Configure DMA for ADC
 */
static void ADCDMAConfigure()
{
	DMACTL0 = DMA1TSEL_26; // ADC12IFGx triggered. reg 0, dma chan 1 trns sel 26, end of conversion trigged
	DMACTL4 = DMARMWDIS; // Read-modify-write disable. reg 4, When accessing the DMA address registers, enable the Read Modify Write disable bit
	DMA1CTL &= ~DMAIFG; // Clear action flag.  chan 1 cntrl, interrupt flag
	DMA1CTL = DMADT_4 + DMADSTINCR_3 + DMASRCINCR_0; // Rpt single tranfer, inc dst. rpt singl transf + DMA dest inc 3 + src address unchaged  
	DMA1SZ = 50; // Total size of transfer region.

	__data16_write_addr((unsigned short) &DMA1SA, (unsigned long) &ADC12MEM12); // write DMA chan 1 src add, ADC12 conv mem
}