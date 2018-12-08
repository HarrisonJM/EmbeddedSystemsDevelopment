/*!
 * @brief Public API functions for interacting with the screen hardware
 * @author Harrison Marcks
 * @date 2/11/2018
 */

#include <msp430.h>
#include "../../helpers/boollint.h"

/*! Defines */
/*!@{*/
#define LCDPIXELMAXX 96
#define LCDPIXELMAXY 96
/*!@}*/

/* init */
extern void LCDInitHardware();

/* Control */
extern void LCDSetCSHigh();
extern bool LCDCheckReady();
extern void LCDWriteCommandOrData(uint16_t commandOrData);
void LCDWaitUntilDone();
void LCDSetCSLow();
