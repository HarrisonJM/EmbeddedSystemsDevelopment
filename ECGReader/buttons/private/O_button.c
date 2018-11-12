/*!
 * @brief initiliases our button "objects"
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include "hardwareAbstractions/I_button.h"
#include "O_button.h"

void ButtonS1init(ButtonStore_t* S1)
{
    S1->ReadButton = ReadButtonS1;
}

void ButtonS2init(ButtonStore_t* S2)
{
    S2->ReadButton = ReadButtonS2;
}
