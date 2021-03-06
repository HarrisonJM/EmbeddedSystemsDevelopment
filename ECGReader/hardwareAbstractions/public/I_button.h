/*!
 * @brief Externs public button functions
 * @author Harrison J Marcks
 * @addtogroup hardwareAbstractions
 * @addtogroup public
 * @date 12/11/2018
 */

#ifndef __I_BUTTON_H__
#define __I_BUTTON_H__

#include <helpers/boollint.h>

/*!
 * @brief Initialises the button hardware
 */
extern void __ButtonHardwareinit(void);
/*!
 * @brief hardware implementation for reading button S2 (right)
 * @return 1 for no press detected, otherwise 0
 */
extern bool __ReadButtonS2(void);
/*!
 * @brief Hardware implementation for reading Button S1 (left)
 * @return 1 for no press detected, otherwise 0
 */
extern bool __ReadButtonS1(void);

#endif /* __I_BUTTON_H__ */
