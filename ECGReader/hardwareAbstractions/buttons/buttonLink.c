/*!
 * @brief Assigns function pointers to the low level button interface
 *
 * @author Harrison J. Marcks
 * @date 9 Nov 18
 */

#include "buttonGet.h"
#include "hardwareAbstractions/I_button.h"

/*!
 * @brief Assigns the Lowlevel implementations with our higher level abstractions
 */
void CreateButtonLinks()
{
    initButtonHardware = &__initButtonHardware;
    ReadButtonS2 = &__ReadButtonS2;
    ReadButtonS1 = &__ReadButtonS1;
}

