/*!
 * @brief This will handle the ECG Reader and how it calculates and displays the data
 *
 * 1) Shift values in Displaybuffer back (left) by 1
 * 2) Get result from ADC (read from memory pool)
 * 3) Calculate the magnitude of result
 * 3) Put pixel where the result is on the far right of the screen (0 is the middleish of the screen)
 * 4) Go back to 1)
 *
 * @author Harrison Marcks
 * @date 9/12/2018
 */

#include <math.h>

#include "helpers/boollint.h"

#include "hardwareAbstractions/public/I_lcd.h"
#include "screen/handler/screenHandler.h"
#include "screen/handler/screenHandlerUtility.h"

#define PI   (double)3.141592653 /* pi */
#define PHIS (double)0.017453293 /* Radians */

/* MISRA C: Ignored here because Hardware Abstraction */
/*! @brief The middle of the screen/Middle pixel */
#define GRAPHZERO ((LCDPIXELMAXY-1)/2)+1

/* Prototypes */
void ActivityECGEnter(void);
void ActivityECGTimer(void);
void __ShiftBuffer(void);
int8_t __GetValPos(double *val);
void __generateSineWave(double* sinVal);

/*!
 * @brief Performs Activity initialisation, zeroes out the  display buffer,
 * @todo Starts the ECG work/interrupts?
 */
void ActivityECGEnter(void)
{
    ScreenDisplayBufferInit(' ');
}
/*!
 * @brief Performs timer activity work. Only run when the ADC has a value
 */
void ActivityECGTimer(void)
{
    double rawVal = 0.0; /* Get value from ADC */
    uint8_t y = 0;

    ScreenShiftBuffer();

    __generateSineWave(&rawVal);
    y = __GetValPos(&rawVal);

    ScreenFlushDisplayBuffer();
}
/*!
 * @brief Figures out where to put the value. Currently designed for sine waves
 *
 * The top of the display (0) represents 1, the bottom of the display (94) represents -1
 * 0 -> 94 gives 95 possible spaces (0.021052632 per pixel, 0.02*95 = 1.9). 0 or the middle is at 48
 * So for every ~ 0.02 away from 0 our value is, move the pixel up by 1
 *
 * Or the display is between 100 and -100. Making every pixel ~2
 *
 * @return The position to print the pixel
 * @todo tidy up!
 */
int8_t __GetValPos(double *val)
{
    /* Previous value for predicting the next value */
    static int32_t prevValue = 0;

    /* MISRA C: I don't want the precision here */
    /* normalise our value*/
    int32_t newVal = (double)(*val)*(int32_t)100;
    /* Negative flag */
    bool negative = false;
    /* Value predicter */
    bool rising = false;
    /* How far away from Zero/the middle is it? */
    uint32_t fromZero = 0;
    uint8_t modulo = 0;
    /* Where the pixel must be placed */
    int8_t yPos = GRAPHZERO;

    /* Check if below zero */
    if(*val < (double)0)
    {
        negative = true;
        (*val) = (*val) * (double)-1.0;
    }
    /* Check if value high or lower than previous */
    if(newVal > prevValue)
    {
        rising = true;
    }

    /*! @todo move to memory */
    /* MISRA C: The modulo will never be higher than 1 */
    /* If our value is odd, predict it's position based on previous value */
    modulo = newVal%2;
    /* How many times is it away from 0 */
    fromZero = newVal/(int32_t)2;

    if(negative == true)
    {
        yPos -= (int8_t)fromZero;
    }
    else
    {
        yPos += (int8_t)fromZero;
    }

    /* If it is odd and it is rising*/
    if((uint8_t)0 != modulo)
    {
        if(true == rising)
        {
            yPos++;
        }
        else
        {
            yPos--;
        }
    }

    return yPos;
}
/*!
 * @brief Generates a test wave
 */
void __generateSineWave(double* sinVal, uint16_t time)
{
    double sineVals[] =
    {0,
     0.052336,
     0.104528,
     0.156434,
     0.207912,
     0.258819,
     0.309017,
     0.358368,
     0.406737,
     0.45399,
     0.5,
     0.544639,
     0.587785,
     0.62932,
     0.669131,
     0.707107,
     0.743145,
     0.777146,
     0.809017,
     0.838671,
     0.866025,
     0.891007,
     0.913545,
     0.93358,
     0.951057,
     0.965926,
     0.978148,
     0.987688,
     0.994522,
     0.99863,
     1,
     0.99863,
     0.994522,
     0.987688,
     0.978148,
     0.965926,
     0.951057,
     0.93358,
     0.913545,
     0.891007,
     0.866025,
     0.838671,
     0.809017,
     0.777146,
     0.743145,
     0.707107,
     0.669131,
     0.62932,
     0.587785,
     0.544639,
     0.5,
     0.453991,
     0.406737,
     0.358368,
     0.309017,
     0.258819,
     0.207912,
     0.156434,
     0.104528,
     0.052336,
     5.89793e-10,
     -0.052336,
     -0.104528,
     -0.156434,
     -0.207912,
     -0.258819,
     -0.309017,
     -0.358368,
     -0.406737,
     -0.45399,
     -0.5,
     -0.544639,
     -0.587785,
     -0.62932,
     -0.669131,
     -0.707107,
     -0.743145,
     -0.777146,
     -0.809017,
     -0.838671,
     -0.866025,
     -0.891007,
     -0.913545,
     -0.93358,
     -0.951057,
     -0.965926,
     -0.978148,
     -0.987688,
     -0.994522,
     -0.99863,
     -1
    };

    *sinVal = sineVals[time];
    if(time > sizeof(sineVals))
        time = 0;
    else
        ++time;
}












