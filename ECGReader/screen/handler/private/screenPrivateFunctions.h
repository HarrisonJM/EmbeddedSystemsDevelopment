/*!
 * @brief Declarations for low-level screen functions
 * @author Harrison Marcks
 * @date 9/12/2018
 */

#ifndef __SCREEN_PRIVATE_FUNCTIONS_H__
#define __SCREEN_PRIVATE_FUNCTIONS_H__

#include "helpers/boollint.h"

extern void __ScreenDisplayBufferInit(char setting
                                      , uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);
extern char __ReverseByte(char inByte);
extern void __ScreenPrintChar(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]
                       , uint8_t x
                       , uint8_t y
                       , const char ch
                       , bool invert);
extern void __ScreenSetText(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]
                     , uint8_t x
                     , uint8_t y
                     , const char* str_p
                     , bool invert);
void __ScreenPrintPixel(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]
                        , uint8_t x
                        , uint8_t y
                        , bool invert);
void __ScreenPrint(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]
                   , const char* str_p
                   , bool invert);
void __ScreenShiftBuffer(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);
void __ScreenFlushDisplayBuffer(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);

void __DeadBeefCow(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);
void __DeadBeefText(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);
void __ScreenSplashScreen(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);

#endif /* __SCREEN_PRIVATE_FUNCTIONS_H__ */
