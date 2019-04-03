/*!
 * @brief initiliases our button "objects"
 * @author Harrison J Marcks
 * @addtogroup buttons
 * @{
 * @addtogroup private
 * @{
 * @date 12/11/2018
 */

#include "hardwareAbstractions/public/I_button.h"
#include "O_button.h"

/*!
 * @brief Initilises the button read FP in the button struct for S1
 * @param S1 The buttonstore for buttonS1
 */
void ButtonS1Init(ButtonStore_t* S1)
{
    S1->ReadButton = __ReadButtonS1;
}
/*!
 * @brief Initialises the button read FP in the button struct for S2
 * @param S2 The buttonstore for button S2
 */
void ButtonS2Init(ButtonStore_t* S2)
{
    S2->ReadButton = __ReadButtonS2;
}

/*! @} @} */
