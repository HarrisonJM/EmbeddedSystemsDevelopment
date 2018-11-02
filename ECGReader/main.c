#include <msp430.h> 

/*
 * main.c
 */
#include "lcdHandler.h"
#include "timer.h"
#include "ADC_1.h"
#include "stdio.h"
#include "string.h"

int main(void)
{
    char adcRdg [5];
    char doneReading = 0;

    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode

    initTimer();
    initDisplay();
    outputDisplayBuffer(0, 96);
    _BIS_SR (GIE);

    setText(0, 1, "A-D chnl 12 ");
    outputDisplayBuffer(0,96);
    adc_1();
    while (1)
    {
        if (adcReading == 1)
        {
            if (doneReading == 0)
            {
                setText (0, 24, "    ");
                sprintf (adcRdg, "%d", rdg);
                setText(0, 24, adcRdg);
                setText(40, 24,"bits");
                outputDisplayBuffer(0, 96);
                doneReading = 1;
            }

        }
        else
        {
            doneReading = 0;
        }

    }

    return 0;
}
