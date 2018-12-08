/*!
 * @brief LCD hardware abstraction
 * @author Harrison Marcks
 * @date 2/12/2018
 */

#include "../public/I_lcd.h"

/*!
 * @brief Inits the hardware and pins for the LCD, including interrupts and SPI
 */
void LCDInitHardware()
{
    /* LCD */
    P4DIR |= 0x04; /* Set P4.2 to output direction (LCD Power On) */
    P4DIR |= 0x08; /* Set P4.3 to output direction (LCD Enable) */

    /* SPI Ports */
    P1SEL0 &= ~0x40; /* Set P1.6 to output direction (SPI MOSI) */
    P1SEL1 |= 0x40; /* Set P1.6 to output direction (SPI MOSI) */
    P1DIR |= 0x40; /* Set P1.6 to output direction (SPI MOSI) */
    P2SEL0 &= ~0x04; /* Set P2.2 to SPI mode (SPI CLK) */
    P2SEL1 |= 0x04; /* Set P2.2 to SPI mode (SPI CLK) */
    P2DIR |= 0x04; /* Set P2.2 to output direction (SPI CLK) */
    P2DIR |= 0x10; /* Set P2.4 to output direction (SPI CS) */

    /* SPI Interface */
    UCB0CTLW0 |= UCSWRST;
    UCB0CTLW0 &= ~(UCCKPH + UCCKPL + UC7BIT + UCMSB);
    UCB0CTLW0 &= ~(UCSSEL_3);
    UCB0CTLW0 |= UCSSEL__SMCLK;
    UCB0BRW = 8;
    UCB0CTLW0 |= (UCMSB + UCCKPH + 0x00 + UCMST + UCSYNC + UCMODE_0);
    UCB0CTLW0 &= ~(UCSWRST);

    P4OUT |= 0x04; /* Turn LCD Power On */
    P4OUT |= 0x08; /* Enable LCD */
    P1OUT &= ~0x01; /* Set P1.0 off (Green LED) */
}
/*!
 * @brief Switches to the LCD chip on the SPI interface
 */
void LCDSetCSHigh()
{
    P2OUT |= 0x10; /* LCD CS high, CHIP SELECT */
}
/*!
 * @brief Checks interrupt flag for ready signal
 * @return 0 if not ready
 */
bool LCDCheckReady()
{
    return (UCB0IFG & UCTXIFG);
}
/*!
 * @brief Writes commands or data to the LCD
 */
void LCDWriteCommandOrData(uint16_t commandOrData)
{
    while(!LCDCheckReady());

    UCB0TXBUF = commandOrData;
}
/*!
 * @brief Waits until the Screen is done writing
 * @todo While loops could be moved out to an interrupt! (check the information popups!)
 */
void LCDWaitUntilDone()
{
    /*! @brief UCB0STATW = the sci status word. UCBBUSY = busy bit (set for start, cleared for stop)*/
    while ((UCB0STATW & UCBBUSY))
    {
        /*! @brief Waits until the device is no longer busy */
    }
}
/*!
 * @brief Sets the Chip select back to low
 */
void LCDSetCSLow()
{
    P2OUT &= ~0x10; /* LCD CS low, CHIP SELECT */
}

