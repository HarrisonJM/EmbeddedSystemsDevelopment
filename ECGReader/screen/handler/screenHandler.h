/*!
 * @brief Public declarations for printing to the screen
 * @author Harrison Marcks
 * @date 2/11/2018
 */

#ifndef LCDHANDLER_H_
#define LCDHANDLER_H_

#include "screenHandlerUtility.h"
#include "../../hardwareAbstractions/public/I_lcd.h"
#include "../../helpers/boollint.h"


extern void ScreenDisplayBufferInit(char setting);

/* Normal printing functions */
extern void ScreenPrintChar(uint8_t x
                            , uint8_t y
                            , const char ch
                            , bool invert);
extern void ScreenSetText(uint8_t x
                          , uint8_t y
                          , const char *str_p
                          , bool invert);
extern void ScreenPrint(const char* str_p
                        , bool invert);
extern void ScreenPrintPixel(uint8_t x
                             , uint8_t y
                             , bool invert);
extern void ScreenShiftBuffer(void);
extern void ScreenFlushDisplayBuffer(void);

/* Functions for printing to custom DisplayBuffers */
extern void ScreenPrintCharCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX]
                                  , uint8_t x
                                  , uint8_t y
                                  , const char ch
                                  , bool invert);
extern void ScreenSetTextCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX]
                                , uint8_t x
                                , uint8_t y
                                , const char *str_p
                                , bool invert);
extern void ScreenPrintCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX]
                       , const char* str_p
                       , bool invert);
extern void ScreenPrintPixelCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX]
                            , uint8_t x
                            , uint8_t y
                            , bool invert);
extern void ScreenFlushDisplayBufferCustom(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);

#endif /* LCDHANDLER_H_ */
