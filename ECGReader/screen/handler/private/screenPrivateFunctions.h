/*!
 * @brief Declarations for low-level screen functions
 * @author Huseyin Sert, Harrison Marcks
 * @addtogroup screen
 * @{
 * @addtogroup handler
 * @{
 * @addtogroup private
 * @{
 * @date 9/12/2018
 */

#ifndef __SCREEN_PRIVATE_FUNCTIONS_H__
#define __SCREEN_PRIVATE_FUNCTIONS_H__

#include "helpers/boollint.h"
/*!
 * @brief Initialise the display buffer
 * @param setting Pass in character to print across screen
 * @param DB_a The display buffer we'd like to print to
 */
extern void __ScreenDisplayBufferInit(char setting
                                      , uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);
/*!
 * @brief Inverts the byte passed to it
 * @param inByte the char to convert
 */
extern char __ReverseByte(char inByte);
/*!
 * @brief Sets the display buffer to contain a single char in the given position
 * @param DB_a The display buffer we'd like to print to
 * @param x The pixel column we wish to print to (Actual number, 0->LCDPIXELMAXX)
 * @param y The row we wish to print to (in pixel location 0->LCDPIXELMAXY
 * @param ch The character we wish to print
 * @param invert Whether to invert the text colour (true for black background/white text)
 */
extern void __ScreenPrintChar(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]
                       , uint8_t x
                       , uint8_t y
                       , const char ch
                       , bool invert);
/*!
 * @brief Writes pixels to where they are wanted on the screen to the displayBuffer
 * @param DB_a The display buffer we'd like to print to
 * @param x The column to start printing, in pixels (multiples of 8)
 * @param y The row to start printing, in pixels (multiples of 8)
 * @param str_p The string we wish to print
 * @param invert true to invert text (black background)
 */
extern void __ScreenSetText(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]
                     , uint8_t x
                     , uint8_t y
                     , const char* str_p
                     , bool invert);
/*!
 * @brief Prints a pixel to the provided display buffer
 * @param DB_a The display buffer we'd like to print to
 * @param x The x co-ordinate to print the pixel
 * @param y The y co-ordinate to print the pixel
 * @param invert Whether to invert the square or not
 */
void __ScreenPrintPixel(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]
                        , uint8_t x
                        , uint8_t y
                        , bool invert);
/*!
 * @brief Writes lines from the top left, down the screen
 * @param DB_a The display buffer we'd like to print to
 * @param str_p The string we wish to print
 * @param invert true to set background black/white text
 */
void __ScreenPrint(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]
                   , const char* str_p
                   , bool invert);
/*!
 * @brief shifts the displaybuffer backwards (left) ish
 * @param DB_a The display buffer we'd like to print to
 */
void __ScreenShiftBuffer(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);
/*!
 * @brief Prints to the display itself
 *
 * @param DB_a The array/double pointer to where the display buffer is stored
 */
void __ScreenFlushDisplayBuffer(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);

void __DeadBeefCow(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);
void __DeadBeefText(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);
void __ScreenSplashScreen(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);

#endif /* __SCREEN_PRIVATE_FUNCTIONS_H__ */

/*! @} @} @} */
