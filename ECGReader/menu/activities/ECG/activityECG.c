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

#include "helpers/boollint.h"

#include "hardwareAbstractions/public/I_lcd.h"
#include "screen/handler/screenHandler.h"
#include "screen/handler/screenHandlerUtility.h"

#define PI 3.141592653 /* pi */
#define PHIS PI/180 /* Radians */

/*! @brief The middle of the screen/Middle pixel */
#define GRAPHZERO ((LCDPIXELMAXY-1)/2)+1

/* File scoped variables */
//static uint8_t GraphDisplayBuffer[LCDPIXELMAXY][SCREENMAXX];

/* Prototypes */
void __ShiftBuffer();

/*!
 * @brief Performs Activity initialisation, zeroes out the  display buffer,
 * @todo Starts the ECG work/interrupts?
 */
void activityECGEnter()
{
    uint8_t y = 0;
    uint8_t x = 0;

    for(; y < LCDPIXELMAXY; ++y)
    {
        for(; x < SCREENMAXX; ++x)
        {
//            GraphDisplayBuffer[y][x] = 0X00;
        }
    }
}
/*!
 * @brief Performs timer activity work. Only run when the ADC has a value
 */
void activityECGTimer()
{
    double rawVal = 0.0; /* Get value from ADC */

    __ShiftBuffer();

    uint8_t i = 0;
    for(; i < LCDPIXELMAXX; ++i)
    {
        //ScreenPrintPixel(i, 16, false);
    }

    ScreenPrint("TEST", false);


    ScreenSetText(0, 16, "TEST2", false);
    ScreenFlushDisplayBuffer();
}
/*!
 * @brief shifts the displaybuffer backwards (left) ish
 */
void __ShiftBuffer()
{
    uint8_t x = 0;
    uint8_t y = 0;

    for(; y < LCDPIXELMAXY-1; ++y)
    {
        for(; x < SCREENMAXX-1; ++x)
        {
//            GraphDisplayBuffer[y][x] = GraphDisplayBuffer[y][x+1];
        }
    }
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
int8_t __GetValPos(double val)
{
    /* Previous value for predicting the next value */
    static int prevValue = 0;

    /* normalise our value*/
    int32_t newVal = val*100;
    /* Negative flag */
    bool negative = false;
    /* Value predicter */
    bool rising = false;
    /* How far away from Zero/the middle is it? */
    uint8_t fromZero = 0;
    uint8_t modulo = 0;
    /* Where the pixel must be placed */
    int8_t yPos = GRAPHZERO;

    /* Check if below zero */
    if(val < 0)
    {
        negative = true;
        val = val * (double)-1.0;
    }
    /* Check if value high or lower than previous */
    if(val > prevValue)
    {
        rising = true;
    }

    /*! @todo move to memory */
    /* If our value is odd, predict it's position based on previous value */
    modulo = newVal%2;
    /* How many times is it away from 0 */
    fromZero = newVal/2;

    if(negative == true)
    {
        yPos -= fromZero;
    }
    else
    {
        yPos += fromZero;
    }

    /* If it is odd and it is rising*/
    if(0 != modulo)
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
void __generateSineWave()
{

}















