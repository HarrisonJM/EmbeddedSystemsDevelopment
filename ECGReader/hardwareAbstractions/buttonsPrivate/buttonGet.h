/*!
 * @brief Declarations for button functions
 */

#ifndef __BUTTON_GET_H__
#define __BUTTON_GET_H__

#include <msp430.h>

#include <hardwareAbstractions/buttonsPrivate/buttonGet.h>
#include "../../helpers/boollint.h"

void __ButtonHardwareinit();
bool __ReadButtonS2();
bool __ReadButtonS1();

#endif /* __BUTTON_GET_H__ */
