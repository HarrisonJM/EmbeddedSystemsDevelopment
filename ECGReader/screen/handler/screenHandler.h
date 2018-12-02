/*!
 * @brief Public declarations for printing to the screen
 * @author Harrison Marcks
 * @date 2/11/2018
 */

#ifndef LCDHANDLER_H_
#define LCDHANDLER_H_

#include "../../helpers/boollint.h"

#define LCDPIXELMAXX 95
#define LCDPIXELMAXY 95

extern void ScreenDisplayBufferInit(char setting);
extern void ScreenPrintChar(uint8_t x
                     , uint8_t y
                     , const char ch
                     , bool invert);
extern void ScreenSetText(uint8_t x
                    , uint8_t y
                    , const char *str_p
                    , bool invert);
void ScreenPrint(const char* str_p
                 , bool invert);
void ScreenFlushDisplayBuffer();

#endif /* LCDHANDLER_H_ */
