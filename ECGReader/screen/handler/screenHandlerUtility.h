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
#define CHARPIXELWIDTH (uint8_t)8 /*! < The size of a character */
#define SCREENMAXX (uint8_t)(LCDPIXELMAXX / CHARPIXELWIDTH) /*! < The maximum size of the screen along the X */
#define SCREENMAXY (uint8_t)(LCDPIXELMAXY / CHARPIXELWIDTH) /*! < The maximum size of the screen along the Y */
/*!@}*/

#endif /* __SCREEN_HANDLER_UTILITY_H__ */
