
#include <msp430fr5969.h>

void initPort1Interrupt()
{
    P1SEL &= (~BIT1); // Set P1.1 SEL as GPIO
    P1DIR &= (~BIT1); // Set P1.1 SEL as Input
    P1IES |= (BIT1); // Falling Edge
    P1IFG &= (~BIT1); // Clear interrupt flag for P1.1
    P1IE |= (BIT1); // Enable interrupt for P1.1
}

void initPort4Interrupt()
{
    P4SEL &= (~BIT5); // Set P1.3 SEL as GPIO
    P4DIR &= (~BIT5); // Set P1.3 SEL as Input
    P4IES |= (BIT5); // Falling Edge
    P4IFG &= (~BIT5); // Clear interrupt flag for P1.3
    P4IE |= (BIT5); // Enable interrupt for P1.3
}