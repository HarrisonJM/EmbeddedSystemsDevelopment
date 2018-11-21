/*!
 * @brief Assigns function pointers to the low level button interface
 *
 * @author Harrison J. Marcks
 * @date 9 Nov 18
 */

#include <hardwareAbstractions/buttonsPrivate/buttonGet.h>
#include "hardwareAbstractions/I_button.h"

/*!
 * @brief Assigns the low-level implementations with our higher level abstractions
 */
void CreateButtonLinks()
{
    initButtonHardware = &__initButtonHardware;
    ReadButtonS2 = &__ReadButtonS2;
    ReadButtonS1 = &__ReadButtonS1;
}

