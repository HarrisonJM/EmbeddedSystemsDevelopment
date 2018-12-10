/*!
 * @brief Utility definitons for the screen handler
 * @author Harrison Marcks
 * @date 10/12/18
 */

#ifndef __SCREEN_HANDLER_UTILITY_H__
#define __SCREEN_HANDLER_UTILITY_H__

#include "../../hardwareAbstractions/public/I_lcd.h"

/*! Definitions */
/*!@{*/
#define CHARPIXELWIDTH 8 /*! < The size of a character */
#define SCREENMAXX (LCDPIXELMAXX / CHARPIXELWIDTH) /*! < The maximum size of the screen along the X */
#define SCREENMAXY (LCDPIXELMAXY / CHARPIXELWIDTH) /*! < The maximum size of the screen along the Y */
/*!@}*/

#endif /* __SCREEN_HANDLER_UTILITY_H__ */
