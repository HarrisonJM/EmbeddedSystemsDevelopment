/*!
 * @brief direct handler for printing to the LCD screen
 * @author Huseyin Sert, Harrison Marcks
 * @date 30/11/2018
 */

#include <stdlib.h>

#include "screen/handler/screenHandler.h"
#include "screenPrivateFunctions.h"

#include "helpers/boollint.h"
#include "font8x8Basic.h"

/* The display buffer we're using */
uint8_t DisplayBuffer[LCDPIXELMAXY][SCREENMAXX];

/*!
 * @brief Initialise the display buffer
 * @param setting Pass in character to print across screen
 */
void ScreenDisplayBufferInit(char setting)
{
    __ScreenDisplayBufferInit(0xFF
                              , &DisplayBuffer);
}

void ScreenPrintChar(uint8_t x
                    , uint8_t y
                    , const char ch
                    , bool invert)
{
    __ScreenPrintChar(DisplayBuffer, x, y, ch, invert);
}
void ScreenSetText(uint8_t x
                  , uint8_t y
                  , const char *str_p
                  , bool invert)
{
    __ScreenSetText(DisplayBuffer, x, y, str_p, invert);
}
void ScreenPrint(const char* str_p
                 , bool invert)
{
    __ScreenPrint(DisplayBuffer, str_p, invert);
}
/*!
 * @brief prints a pixel to the default display Buffer
 * @param x The x co-ordinate to print the pixel
 * @param y The y co-ordinate to print the pixel
 * @param invert Whether to invert the square or not
 */
void ScreenPrintPixel(uint8_t x,
                      uint8_t y,
                      bool invert)
{
    __ScreenPrintPixel(DisplayBuffer, x, y, invert);
}
/*!
 * @brief Shifts everything in the buffer << left << by a single pixel
 */
void ScreenShiftBuffer(void)
{
    __ScreenShiftBuffer(DisplayBuffer);
}
/*!
 * @brief Flush the normal display buffer
 */
void ScreenFlushDisplayBuffer()
{
    __ScreenFlushDisplayBuffer(DisplayBuffer);
}


/* Custom Display Buffer functions */
/*!
 * @brief Prints a pixel to the provided display buffer
 * @param customDB The display buffer we'd like to print to
 * @param x The x co-ordinate to print the pixel
 * @param y The y co-ordinate to print the pixel
 * @param invert Whether to invert the square or not
 */
void ScreenPrintPixelCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX],
                            uint8_t x,
                            uint8_t y,
                            bool invert)
{
    __ScreenPrintPixel(customDB, x, y, invert);
}

/*!
 * @brief Sets the display buffer to contain a single char in the given position
 * @param customDB The display buffer we'd like to print to
 * @param x The pixel column we wish to print to (Actual number, 0->LCDPIXELMAXX)
 * @param y The row we wish to print to (in pixel location 0->LCDPIXELMAXY
 * @param ch The character we wish to print
 * @param invert Whether to invert the text colour (true for black background/white text)
 */
void ScreenPrintCharCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX]
                                  , uint8_t x
                                  , uint8_t y
                                  , const char ch
                                  , bool invert)
{
    __ScreenPrintChar(customDB, x, y, ch, invert);
}
/*!
 * @brief Writes pixels to where they are wanted on the screen to the displayBuffer
 * @param customDB The display buffer we'd like to print to
 * @param x The column to start printing, in pixels (multiples of 8)
 * @param y The row to start printing, in pixels (multiples of 8)
 * @param str_p The string we wish to print
 * @param invert true to invert text (black background)
 */
void ScreenSetTextCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX]
                                , uint8_t x
                                , uint8_t y
                                , const char *str_p
                                , bool invert)
{
    __ScreenSetText(customDB, x, y, str_p, invert);
}
/*!
 * @brief Writes lines from the top left, down the screen
 * @param customDB The display buffer we'd like to print to
 * @param str_p The string we wish to print
 * @param invert true to set background black/white text
 */
void ScreenPrintCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX]
                       , const char* str_p
                       , bool invert)
{
    __ScreenPrint(customDB, str_p, invert);
}
/*!
 * @brief Flushes a custom display buffer to the screen
 * @param customDB The display buffer we'd like to print to
 */
void ScreenFlushDisplayBufferCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX])
{
    __ScreenFlushDisplayBuffer(customDB);
}
/*!
 * @brief Creates a splash screen for 5 seconds before it goes in to the main menu
 *
 */
void ScreenSplash()
{
    __ScreenSplashScreen(DisplayBuffer);
}
