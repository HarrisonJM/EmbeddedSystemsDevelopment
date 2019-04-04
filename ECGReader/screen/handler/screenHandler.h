/*!
 * @brief Public declarations for printing to the screen
 * @author Huseyin Sert, Harrison Marcks
 * @addtogroup screen
 * @{
 * @addtogroup handler
 * @{
 * @date 2/11/2018
 */

#ifndef LCDHANDLER_H_
#define LCDHANDLER_H_

#include "screenHandlerUtility.h"
#include "../../hardwareAbstractions/public/I_lcd.h"
#include "../../helpers/boollint.h"

/*!
 * @brief (deprecated) Old display buffer init (deprecated)
 */
extern void ScreenDisplayBufferInit(char setting);

/* Normal printing functions */
/*!
 * @brief Prints ch to _the_ display buffer
 * @param x The X co-ordinate we wish to print to (up to SCREENMAXX)
 * @param y The X co-ordinate we wish to print to (up to LCDPIXELMAXY)
 * @param ch The char we wish to print
 * @param invert whether to invert the character or not
 */
extern void ScreenPrintChar(uint8_t x
                            , uint8_t y
                            , const char ch
                            , bool invert);
/*!
 * @brief Prints a string to the screen
 * @param x The X co-ordinate we wish to print to (up to SCREENMAXX)
 * @param y The X co-ordinate we wish to print to (up to LCDPIXELMAXY)
 * @param str_p A pointer to the string we wish to print
 * @param invert whether to invert the character or not
 */
extern void ScreenSetText(uint8_t x
                          , uint8_t y
                          , const char *str_p
                          , bool invert);
/*!
 * @brief Prints a string the screen from 0 and handles newlines and screen edge
 * @param str_p The string we wish to print to the screen
 * @param invert whether to invert the character or not
 */
extern void ScreenPrint(const char* str_p
                        , bool invert);
/*!
 * @brief Print a pixel to the screen
 * @param x The X co-ordinate we wish to print to (up to SCREENMAXX)
 * @param y The X co-ordinate we wish to print to (up to LCDPIXELMAXY)
 * @param invert whether to invert the character or not
 */
extern void ScreenPrintPixel(uint8_t x
                             , uint8_t y
                             , bool invert);
/*!
 * @brief Shifts the contents of the display buffer
 */
extern void ScreenShiftBuffer(void);
/*!
 * @brief flushes the contents of the display buffer tot he screen
 */
extern void ScreenFlushDisplayBuffer(void);
/*!
 * @brief Prints the splash image to the screen
 */
extern void ScreenSplash(void);

/* Functions for printing to custom DisplayBuffers */
/*!
 * @brief Prints ch to _the_ display buffer
 * @param customDB a pointer to the custom diplsaybuffer we wish to print to
 * @param x The X co-ordinate we wish to print to (up to SCREENMAXX)
 * @param y The X co-ordinate we wish to print to (up to LCDPIXELMAXY)
 * @param ch The char we wish to print
 * @param invert whether to invert the character or not
 */
extern void ScreenPrintCharCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX]
                                  , uint8_t x
                                  , uint8_t y
                                  , const char ch
                                  , bool invert);
/*!
 * @brief Prints a string to the screen
 * @param customDB a pointer to the custom diplsaybuffer we wish to print to
 * @param x The X co-ordinate we wish to print to (up to SCREENMAXX)
 * @param y The X co-ordinate we wish to print to (up to LCDPIXELMAXY)
 * @param str_p A pointer to the string we wish to print
 * @param invert whether to invert the character or not
 */
extern void ScreenSetTextCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX]
                                , uint8_t x
                                , uint8_t y
                                , const char *str_p
                                , bool invert);
/*!
 * @brief Prints a string the screen from 0 and handles newlines and screen edge
 * @param customDB a pointer to the custom diplsaybuffer we wish to print to
 * @param str_p The string we wish to print to the screen
 * @param invert whether to invert the character or not
 */
extern void ScreenPrintCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX]
                       , const char* str_p
                       , bool invert);
/*!
 * @brief Print a pixel to the screen
 * @param customDB a pointer to the custom diplsaybuffer we wish to print to
 * @param x The X co-ordinate we wish to print to (up to SCREENMAXX)
 * @param y The X co-ordinate we wish to print to (up to LCDPIXELMAXY)
 * @param invert whether to invert the character or not
 */
extern void ScreenPrintPixelCustom(uint8_t customDB[LCDPIXELMAXY][SCREENMAXX]
                            , uint8_t x
                            , uint8_t y
                            , bool invert);
/*!
 * @brief Flushes the contents of the display buffer to the screen
 * @param customDB a pointer to the custom diplsaybuffer we wish to print to
 */
extern void ScreenFlushDisplayBufferCustom(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]);

#endif /* LCDHANDLER_H_ */

/*! @} @} */
