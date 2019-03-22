/*!
 * @brief Public API functions for interacting with the screen hardware
 * @author Harrison Marcks
 * @date 2/11/2018
 */

#ifndef __I_LCD_H__
#define __I_LCD_H__

#include <msp430fr5969.h>
#include "../../helpers/boollint.h"

/*! Defines */
/*!@{*/
#define LCDPIXELMAXX (uint8_t)96
#define LCDPIXELMAXY (uint8_t)96
/*!@}*/

/* init */
extern void LCDInitHardware(void);

/* Control */
extern void LCDSetCSHigh(void);
extern bool LCDCheckReady(void);
extern void LCDWriteCommandOrData(uint16_t commandOrData);
void LCDWaitUntilDone(void);
void LCDSetCSLow(void);

#endif /* __I_LCD_H__ */
