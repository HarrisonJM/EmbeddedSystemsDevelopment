///*
// * @brief Slider handler implementation
// * @author Harrison Marcks
// * @date 12/12/2018
// */
//
//#include <msp430.h>
//
//#define NOOFELEMENTS    6
//#define LEFT_UPPER      0
//#define LEFT_CENTRE     1
//#define LEFT_LOWER      2
//#define RIGHT_UPPER     3
//#define RIGHT_CENTRE    4
//#define RIGHT_LOWER     5
//
//
//void SliderInit
//{
//    // Capacitive Touch.
//    CAPTIO0CTL = CAPTIOEN + (3<<4) + (4<<1);
//}
//
//void SliderGenericHandler()
//{
//    /* Capture initialisation. */
//    TA2CTL |= TACLR;
//    /* Clear the capacitance counter, set the trigger input to GND. */
//    TA2CCTL0 = CM_1+CCIS_2+CAP+SCS;
//    /* Clear gate flags. */
//    TA3CTL &= ~CCIFG;
//    TA3CTL |= TACLR;
//    /* Put the CPU to sleep, for ACCUMULATION_CYCLES of SMCLK. */
//    __bis_SR_register(LPM0_bits+GIE);
//    /* Set capacitance counter trigger to Vcc. */
//    TA2CCTL0 |= CCIS_3 ;
//
//    /* Iterates over all the sensors */
//    if (++elementNumber >= (NOOFELEMENTS ))
//    {
//        elementNumber = 0;
//    }
//
//    switch (elementNumber)
//    {
//    case LEFT_UPPER:
//        CAPTIO0CTL = CAPTIOEN + (3<<4) + (4<<1);
//        break;
//    case LEFT_CENTRE:
//        CAPTIO0CTL = CAPTIOEN + (3<<4) + (5<<1);
//        break;
//    case LEFT_LOWER:
//        CAPTIO0CTL = CAPTIOEN + (3<<4) + (6<<1);
//        break;
//    case RIGHT_UPPER:
//        CAPTIO0CTL = CAPTIOEN + (1<<4) + (5<<1);
//        break;
//    case RIGHT_CENTRE:
//        CAPTIO0CTL = CAPTIOEN + (1<<4) + (4<<1);
//        break;
//    case RIGHT_LOWER:
//        CAPTIO0CTL = CAPTIOEN + (1<<4) + (3<<1);
//        break;
//    }
//}
