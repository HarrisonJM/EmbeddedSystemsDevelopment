/*!
 * @brief defines the main entry point for the program
 * @date 10/12/2018
 * @todo TIDY EVERYTHING
 */

#include <msp430.h> 
#include "handlers.h"

int restarting;

/*
 * main.c
 */
int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode
                                    // to activate previously configured port settings

    if (restarting == TRUE) goto restart_here;

    // Initialisation

    // Initialisation - POST/POWER ON

    P1DIR |=  0x01;                 // Set P1.0 to output direction
    P4DIR |=  0x40;                 // Set P4.6 to output direction
    P1OUT &= ~0x01;                 // Set P1.0 off (Green LED)
    P4OUT &= ~0x40;                 // Set P4.6 off (Red LED)
    P4OUT |=  0x40;                 // Set P4.6 on  (Red LED)

    asm(
         "      mov.w #001C00h, R12 \n"
         "loop1: \n"
         "      mov.w #00000h, 0(R12) \n"
         "      cmp.w #00000h, 0(R12) \n"
         "      jne loop1 \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop1 \n"
        );

    P1OUT |=  0x01;                 /* Set P1.0 on  (Green LED) */
    P4OUT &= ~0x40;                 /* Set P4.6 off (Red LED) */

    asm(
         "      mov.w #001C00h, R12 \n"
         "loop2: \n"
         "      mov.w #0ffffh, 0(R12) \n"
         "      cmp.w #0ffffh, 0(R12) \n"
         "      jne loop2 \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop2 \n"
        );

    P1OUT &= ~0x01;                 /* Set P1.0 off (Green LED) */
    P4OUT |=  0x40;                 /* Set P4.6 on  (Red LED) */

    asm(
         "      mov.w #001C00h, R12 \n"
         "loop3: \n"
         "      mov.w #05555h, 0(R12) \n"
         "      cmp.w #05555h, 0(R12) \n"
         "      jne loop3 \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop3 \n"
        );

    P1OUT |=  0x01;                 /* Set P1.0 on  (Green LED) */
    P4OUT &= ~0x40;                 /* Set P4.6 off (Red LED) */

    asm(
         "      mov.w #001C00h, R12 \n"
         "loop4: \n"
         "      mov.w #0aaaah, 0(R12) \n"
         "      cmp.w #0aaaah, 0(R12) \n"
         "      jne loop4 \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop4 \n"
        );

    P1OUT &= ~0x01;                 /* Set P1.0 off (Green LED) */
    P4OUT |=  0x40;                 /* Set P4.6 on  (Red LED) */

    asm(
         "      mov.w #001C00h, R12 \n"
         "loop5: \n"
         "      mov.w R12, 0(R12) \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop5 \n"

         "      mov.w #001C00h, R12 \n"
         "loop6: \n"
         "      cmp.w R12, 0(R12) \n"
         "      jne loop6 \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop6 \n"
        );

    P1OUT |=  0x01;                 /* Set P1.0 on  (Green LED) */
    P4OUT &= ~0x40;                 /* Set P4.6 off (Red LED) */

    asm(
         "      mov.w #001C00h, R12 \n"
         "loop7: \n"
         "      mov.w #00000h, 0(R12) \n"
         "      add #2, R12 \n"
         "      cmp.w #002400h, R12 \n"
         "      jn loop7 \n"
        );

    P1OUT &= ~0x01;                 /* Set P1.0 off (Green LED) */
    P4OUT &= ~0x40;                 /* Set P4.6 off (Red LED) */


    /* Initialisation - hardware */


    P1DIR  |= 0x01;                 /* Set P1.0 to output direction */
    P1DIR  &= ~0x02;                /* Set P1.1 to input direction (switch 2) */
    P1REN  |= 0x02;                 /* Set P1.1 pull-up resistor enabled */
    P1OUT  |= 0x02;                 /* Set P1.1 kick to start input */
    P4DIR  |= 0x40;                 /* Set P4.6 to output direction */


    /* Timer A0 (1ms interrupt) */
    TA0CCR0 =  1024;                /* Count up to 1024 */
    TA0CCTL0 = 0x10;                /* Enable counter interrupts, bit 4=1 */
    TA0CTL =  TASSEL_2 + MC_1;      /* Timer A using subsystem master clock, SMCLK(1.1 MHz)
                                       and count UP to create a 1ms interrupt */



     /* Timer A2 used for capture */
    TA2CTL |= TACLR;
    TA2CTL   = ID_3 + TBSSEL_2 + MC_2;  /* Timer A2 using subsystem master clock, SMCLK(1.1 MHz) */
    TA2CCTL1 = CM_1+CCIS_0+CAP+SCS;     /* Capture set up for Timer A2 */



    /* Capacitive Touch */
    CAPTIO0CTL = CAPTIOEN + (3<<4) + (4<<1);

    P1REN  |= BIT3;
    P1DIR  |= BIT3;
    P1OUT  &= ~BIT3;
    P1REN  |= BIT4;
    P1DIR  |= BIT4;
    P1OUT  &= ~BIT4;
    P1REN  |= BIT5;
    P1DIR  |= BIT5;
    P1OUT  &= ~BIT5;

    P3REN  |= BIT4;
    P3DIR  |= BIT4;
    P3OUT  &= ~BIT4;
    P3REN  |= BIT5;
    P3DIR  |= BIT5;
    P3OUT  &= ~BIT5;
    P3REN  |= BIT6;
    P3DIR  |= BIT6;
    P3OUT  &= ~BIT6;


    /* LCD */
    P4DIR  |= 0x04;                 /* Set P4.2 to output direction (LCD Power On) */
    P4DIR  |= 0x08;                 /* Set P4.3 to output direction (LCD Enable) */

    /* SPI Ports */
    P1SEL0 &= ~0x40;                /* Set P1.6 to output direction (SPI MOSI) */
    P1SEL1 |= 0x40;                 /* Set P1.6 to output direction (SPI MOSI) */
    P1DIR  |= 0x40;                 /* Set P1.6 to output direction (SPI MOSI) */
    P2SEL0 &= ~0x04;                /* Set P2.2 to SPI mode (SPI CLK) */
    P2SEL1 |= 0x04;                 /* Set P2.2 to SPI mode (SPI CLK) */
    P2DIR  |= 0x04;                 /* Set P2.2 to output direction (SPI CLK) */
    P2DIR  |= 0x10;                 /* Set P2.4 to output direction (SPI CS) */

    /* SPI Interface */
    UCB0CTLW0 |= UCSWRST;
    UCB0CTLW0 &= ~(UCCKPH + UCCKPL + UC7BIT + UCMSB);
    UCB0CTLW0 &= ~(UCSSEL_3);
    UCB0CTLW0 |= UCSSEL__SMCLK;
    UCB0BRW    = 8;
    UCB0CTLW0 |= (UCMSB + UCCKPH + 0x00 + UCMST + UCSYNC + UCMODE_0);
    UCB0CTLW0 &= ~(UCSWRST);

    P4OUT |= 0x04;                  /* Turn LCD Power On */
    P4OUT |= 0x08;                  /* Enable LCD */
    P1OUT &= ~0x01;                 /* Set P1.0 off (Green LED) */
    P4OUT &= ~0x40;                 /* Set P4.6 off (Red LED) */

    /* Initialisation - software */

    init_button_handler();
    init_q(&led_q);
    initDisplayWriting();

    _BIS_SR(GIE);                   /* interrupts enabled */


    restart_here:

    WDTCTL = WDTPW + WDTCNTCL + 3;  /* Enable the Watchdog Timer */

    /* Re-set the stack pointer */

    asm(
         "      mov.w #002400h, SP \n"
        );


    /* Background Loop */

    for (;;)
    {
        lcd_handler();

        WDTCTL = WDTPW + WDTCNTCL + 3; /* Kick the watchdog */
    }

    return 0;
}



#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void)    /*  Timer0 A0 1ms interrupt service routine */
{
    counter_button_handler++;
    if (counter_button_handler >= INTERVAL_BUTTON_HANDLER)
    {
        counter_button_handler = 0;
        button_timer();
        led_handler();
        slider_handler();
    }

    /*  Toggle the red LED 500ms on and 500ms off */

    heartbeat++;

    if (heartbeat >= 500)
    {
            heartbeat = 1;
            P1OUT ^= 0x01;        /*  Toggle P1.0 using exclusive-OR */
    }
}



/*  Watchdog interrupt service */
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    WDTCTL = WDTPW + WDTCNTCL + 3; /* Reset the watchdog */
    P4OUT |=  0x40;     /*  Set P4.6 on  (Red LED) */
    restarting = TRUE;
    main();
}

