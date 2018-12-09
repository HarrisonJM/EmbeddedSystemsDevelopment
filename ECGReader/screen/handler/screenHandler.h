/*!
 * @brief Public declarations for printing to the screen
 * @author Harrison Marcks
 * @date 2/11/2018
 */

#ifndef LCDHANDLER_H_
#define LCDHANDLER_H_

#include "../../helpers/boollint.h"

/*! Definitions */
/*!@{*/
#define CHARPIXELWIDTH 8 /*! < The size of a character */
#define SCREENMAXX 12 /*! < The maximum size of the screen along the X */
#define SCREENMAXY 12 /*! < The maximum size of the screen along the Y */
/*!@}*/

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
