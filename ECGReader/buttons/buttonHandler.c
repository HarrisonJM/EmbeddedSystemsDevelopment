/*!
 * @brief Button handler for both buttons. Handles pressed(click), held, and double click
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#include "buttons/buttonS1Handling.h"
#include "buttons/buttonS2Handling.h"
#include "buttonHandlingUtility.h"
/*!
 * @brief Initialises both Handlers' variables
 */
void InitButtonHandler()
{
    InitButtonS1Handler();
    InitButtonS2Handler();
}
