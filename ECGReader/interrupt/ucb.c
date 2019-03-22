#include <msp430fr5969.h>
#include <helpers/boollint.h>

#include <hardwareAbstractions/public/I_lcd.h>
#include <screen/handler/screenHandlerUtility.h>

/* line and column names are now redundant but left in just for piece of mind */
uint32_t column = 0;
uint32_t line = 0;
/*! @brief Write lines (0x80, image update mode ) and VCOM bit (0x40, video communication) */
static const uint8_t command = 0xC0;

extern char __ReverseByte(char inByte);
extern uint8_t DisplayBuffer[LCDPIXELMAXY][SCREENMAXX];

#pragma vector=USCI_B0_VECTOR
__interrupt void UCBSCREEN(void)
{
    switch(UCB0IV) /* Check pin interrupted against */
    {
        default:
            break;
    }
    
    // LCDSetCSHigh();
    // LCDWriteCommandOrData(command);

    // for(line = 0; line < LCDPIXELMAXX; ++line)
    // {
    //     LCDWriteCommandOrData(__ReverseByte(line + 1));

    //     for(column = 0; column < SCREENMAXX; ++column)
    //     {
    //         LCDWriteCommandOrData(DB_a[line][column]);
    //     }
    //     /* EOL byte */
    //     LCDWriteCommandOrData(0x00);
    // }    
}

// #if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
// #pragma vector = USCI_B0_VECTOR
// __interrupt void USCI_B0_ISR(void)
// #elif defined(__GNUC__)
// void __attribute__ ((interrupt(USCI_B0_VECTOR))) USCI_B0_ISR (void)
// #else
// #error Compiler not supported!
// #endif
// {
//     puts("interupt service routine entered\n");
//     switch(__even_in_range(UCB0IV,0x1E)) {
//     case 0x00: break; // Vector 0: No interrupts break;
//     case 0x02: break;

//     case 0x04:
//         UCB0CTLW0 |= UCTXSTT; //resend start if NACK
//     break; // Vector 4: NACKIFG break;

//     case 0x06: break; // Vector 6: STTIFG break;
//     case 0x08: break; // Vector 8: STPIFG break;
//     case 0x0a: break; // Vector 10: RXIFG3 break;
//     case 0x0c: break; // Vector 14: TXIFG3 break;
//     case 0x0e: break; // Vector 16: RXIFG2 break;
//     case 0x10: break; // Vector 18: TXIFG2 break;
//     case 0x12: break; // Vector 20: RXIFG1 break;
//     case 0x14: break; // Vector 22: TXIFG1 break;

//     case 0x16: // Vector 24: RXIFG0 break;
//         *PRxData++ = UCB0RXBUF; // Get RX data
//         RXByteCtr --;
//         if (RXByteCtr == 0) {
//             __delay_cycles(30);
//             UCB0CTLW1 |= UCSWACK;
//             UCB0CTLW0 |= UCTXACK;
//             UCB0CTLW0 |= UCTXSTP;
//         }
//         else {
//             UCB0IFG &= ~UCRXIFG0;
//             __bic_SR_register_on_exit(LPM3_bits);
//         }
//     break;

//     case 0x18:
//         if (TXByteCtr){ // Check TX byte counter
//             UCB0TXBUF = *PTxData++; // Load TX buffer
//             TXByteCtr--;
//         }
//         else {
//             UCB0CTLW0 |= UCTXSTP; // I2C stop condition
//             UCB0IFG &= ~UCTXIFG; // Clear USCI_B0 TX int flag
//             __bic_SR_register_on_exit(LPM3_bits);// Exit LPM0
//         }
//     break; // Vector 26: TXIFG0 break;

//     case 0x1A:
//         UCB0IFG &= ~UCBCNTIFG;
//     break; // Vector 28: BCNTIFG break;

//     case 0x1c: break; // Vector 30: clock low timeout break;
//     case 0x1e: break; // Vector 32: 9th bit break;
//     default: break;
//     }
// }

// void initI2C(void){
//     puts("initialising i2c");
//     UCB0CTLW0 |= UCSWRST; // put eUSCI_B in reset state
//     UCB0CTLW0 |= UCMODE_3 | UCMST | UCSSEL_2 | UCSYNC;// I2C mode, master mode, SMCLk /// + UCSSEL_2 | UCSYNC
//     UCB0CTLW1 |= UCASTP_2; //automatic stop generated
//     //after UCB0TBCNT is reached
//     UCB0BRW = 0x20; // 12
//     UCB0CTLW0 &=~ UCSWRST; //clear reset register
//     UCB0IE |= UCNACKIE | UCBCNTIE;
//     puts("initialising i2c successful");
// }

// void TXdata(unsigned char TX_byte) {
//     puts("calling iic_TX");
//     iic_TX();
//     puts("returned from iic_TX");
//     PTxData = (unsigned char *)&TXDataArr; // TX array start address
//     printf("PTxData = %d", TXDataArr[0]);
//     TXByteCtr = TX_byte; // Load TX byte counter
//     printf("TXByteCtr = %d\n",TX_byte);
//     puts("calling start_TX");
//     start_TX();
// }
// void iic_TX(void) {
//     puts("entered iic_TX \n");
//     printf("slave address = %d \n", SlaveAddress);
//     UCB0I2CSA = SlaveAddress;
//     puts("enabling tx interupt");
//     UCB0IE |= UCTXIE0; // Enable TX interrupt
//     puts("TX interupt enabled \n");
//     puts("exiting iic_TX\n");
// }

// void start_TX(void) {
//     puts("entered start_TX \n");
//     while (UCB0CTLW0 & UCTXSTP); // Ensure stop condition got sent
//     puts("stop condition sent \n");
//     puts("starting i2c TX\n");
//     UCB0CTLW0 |= UCTR + UCTXSTT; // I2C TX, start condition
//     puts("start condition met\n");
//     puts("entering interupt service routine\n");
//     __bis_SR_register(LPM3_bits + GIE); // Enter LPM0 w/ interrupts
//     puts("exiting start_TX\n");
// }

// void init_slave(){
//     puts("initialising sensor");
//     TXDataArr[0] = 0xF4;
//     TXDataArr[1] = BIT5 + BIT2 + BIT1;
//     TXdata(2);
//     puts("initialising sensor successful");
// }

// void read_slave(){
//     puts("reading data from sensor..");
//     RXdata(0xFA, 2);
//     puts("data read");

// }
// #include <msp430.h>

// #include <stdio.h>


// unsigned char SlaveAddress = 0x76;

// unsigned char TXByteCtr;

// unsigned char RXByteCtr;

// unsigned char *PTxData;

// unsigned char *PRxData;


// unsigned char RXData[6];

// unsigned char TXDataArr[3];


// void initI2C(void);

// void RXdata(unsigned char reg_addr, unsigned char RX_byte);

// void TXdata(unsigned char TX_byte);

// void iic_TX(void);

// void iic_RX(void);

// void start_TX(void);

// void start_RX(void);

// void init_slave();

// void read_slave();


// int main(void)

// {

//   WDTCTL = WDTPW | WDTHOLD;


//   //// I/O INIT

//   // Disable the GPIO power-on default high-impedance mode to activate

//   // previously configured port settings

//   PM5CTL0 &= ~LOCKLPM5;

//   P1SEL1 |= BIT6 | BIT7;                    // I2C pins

//   ////


//   initI2C();


//   __bis_SR_register(GIE);


//   init_slave(); 


//   read_slave();


//   while(1)

//   {

//       //read_slave();

//   }

// }


// /////////////////// I2C B0///////////////////

// #if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)

// #pragma vector = USCI_B0_VECTOR

// __interrupt void USCI_B0_ISR(void)

// #elif defined(__GNUC__)

// void __attribute__ ((interrupt(USCI_B0_VECTOR))) USCI_B0_ISR (void)

// #else

// #error Compiler not supported!

// #endif

// {

//     puts("interupt service routine entered\n");

//     switch(__even_in_range(UCB0IV,0x1E)) {

//     case 0x00: break; // Vector 0: No interrupts break;

//     case 0x02: break;


//     case 0x04:

//         UCB0CTLW0 |= UCTXSTT; //resend start if NACK

//     break; // Vector 4: NACKIFG break;


//     case 0x06: break; // Vector 6: STTIFG break;

//     case 0x08: break; // Vector 8: STPIFG break;

//     case 0x0a: break; // Vector 10: RXIFG3 break;

//     case 0x0c: break; // Vector 14: TXIFG3 break;

//     case 0x0e: break; // Vector 16: RXIFG2 break;

//     case 0x10: break; // Vector 18: TXIFG2 break;

//     case 0x12: break; // Vector 20: RXIFG1 break;

//     case 0x14: break; // Vector 22: TXIFG1 break;


//     case 0x16: // Vector 24: RXIFG0 break;

//         *PRxData++ = UCB0RXBUF; // Get RX data

//         RXByteCtr --;

//         if (RXByteCtr == 0) {

//             __delay_cycles(30);

//             UCB0CTLW1 |= UCSWACK;

//             UCB0CTLW0 |= UCTXACK;

//             UCB0CTLW0 |= UCTXSTP;

//         }

//         else {

//             UCB0IFG &= ~UCRXIFG0;

//             __bic_SR_register_on_exit(LPM3_bits);

//         }

//     break;


//     case 0x18:

//         if (TXByteCtr){ // Check TX byte counter

//             UCB0TXBUF = *PTxData++; // Load TX buffer

//             TXByteCtr--;

//         }

//         else {

//             UCB0CTLW0 |= UCTXSTP; // I2C stop condition

//             UCB0IFG &= ~UCTXIFG; // Clear USCI_B0 TX int flag

//             __bic_SR_register_on_exit(LPM3_bits);// Exit LPM0

//         }

//     break; // Vector 26: TXIFG0 break;


//     case 0x1A:

//         UCB0IFG &= ~UCBCNTIFG;

//     break; // Vector 28: BCNTIFG break;


//     case 0x1c: break; // Vector 30: clock low timeout break;

//     case 0x1e: break; // Vector 32: 9th bit break;

//     default: break;

//     }

// }


// void initI2C(void){

//     puts("initialising i2c");

//     UCB0CTLW0 |= UCSWRST; // put eUSCI_B in reset state

//     UCB0CTLW0 |= UCMODE_3 | UCMST | UCSSEL_2 | UCSYNC;// I2C mode, master mode, SMCLk /// + UCSSEL_2 | UCSYNC

//     UCB0CTLW1 |= UCASTP_2; //automatic stop generated

//     //after UCB0TBCNT is reached

//     UCB0BRW = 0x20; // 12

//     UCB0CTLW0 &=~ UCSWRST; //clear reset register

//     UCB0IE |= UCNACKIE | UCBCNTIE;

//     puts("initialising i2c successful");

// }


// void TXdata(unsigned char TX_byte) {

//     puts("calling iic_TX");

//     iic_TX();

//     puts("returned from iic_TX");

//     PTxData = (unsigned char *)&TXDataArr; // TX array start address

//     printf("PTxData = %d", TXDataArr[0]);

//     TXByteCtr = TX_byte; // Load TX byte counter

//     printf("TXByteCtr = %d\n",TX_byte);

//     puts("calling start_TX");

//     start_TX();

// }

// void iic_TX(void) {

//     puts("entered iic_TX \n");

//     printf("slave address = %d \n", SlaveAddress);

//     UCB0I2CSA = SlaveAddress;

//     puts("enabling tx interupt");

//     UCB0IE |= UCTXIE0; // Enable TX interrupt

//     puts("TX interupt enabled \n");

//     puts("exiting iic_TX\n");

// }


// void start_TX(void) {

//     puts("entered start_TX \n");

//     while (UCB0CTLW0 & UCTXSTP); // Ensure stop condition got sent

//     puts("stop condition sent \n");

//     puts("starting i2c TX\n");

//     UCB0CTLW0 |= UCTR + UCTXSTT; // I2C TX, start condition

//     puts("start condition met\n");

//     puts("entering interupt service routine\n");

//     __bis_SR_register(LPM3_bits + GIE); // Enter LPM0 w/ interrupts

//     puts("exiting start_TX\n");

// }


// void init_slave(){

//     puts("initialising sensor");

//     TXDataArr[0] = 0xF4;

//     TXDataArr[1] = BIT5 + BIT2 + BIT1;

//     TXdata(2);

//     puts("initialising sensor successful");

// }


// void read_slave(){

//     puts("reading data from sensor..");

//     RXdata(0xFA, 2);

//     puts("data read");


// }
