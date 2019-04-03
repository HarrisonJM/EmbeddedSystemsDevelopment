/*!
 * @brief Public API functions for interacting with the screen hardware
 * @author Harrison Marcks
 * @addtogroup hardwareAbstractions
 * @addtogroup public
 * @date 2/11/2018
 */

#ifndef __I_LCD_H__
#define __I_LCD_H__

#include <msp430fr5969.h>
#include "../../helpers/boollint.h"

/*! Defines */
/*!@{*/
#define LCDPIXELMAXX ((uint8_t)96)
#define LCDPIXELMAXY ((uint8_t)96)
/*!@}*/

/*!
 * @brief inits the LCD hardware
  */
extern void LCDInitHardware(void);

/* Control */
/*!
 * @brief Set the chip select to high
 */
extern void LCDSetCSHigh(void);
/*!
 * @brief Check the LCD is ready to receive another command
 * @return true if not ready
 */
extern bool LCDCheckReady(void);
/*!
 * @brief Write a command to the LCD
 * @param commandOrData an upto 4-byte command for the LCD
 */
extern void LCDWriteCommandOrData(uint16_t commandOrData);
/*!
 * @brief Checks the LCD is done writing
 */
void LCDWaitUntilDone(void);
/*!
 * @brief Sets the LCD chip select to Low
 */
void LCDSetCSLow(void);

#endif /* __I_LCD_H__ */
