/*!
 * @brief Externs public button functions
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#ifndef __I_BUTTON_H__
#define __I_BUTTON_H__

#include <helpers/boollint.h>

/*!
 * @brief Initialises the button hardware
 */
extern void __initButtonHardware();
/*!
 * @brief hardware implementation for reading button S2 (right)
 * @return 1 for no press detected, otherwise 0
 */
extern bool __ReadButtonS2();
/*!
 * @brief Hardware implementation for reading Button S1 (left)
 * @return 1 for no press detected, otherwise 0
 */
bool __ReadButtonS1();

#endif /* __I_BUTTON_H__ */
