/*!
 * @brief Implementation for grabbing button information
 * @author Harrison J Marcks
 * @date 8 Nov 2018
 */

#include "buttonGet.h"

int __ButtonReadS2()
{
    int bucket = 0;
    int returnVal = 1;

    while((P1IN & 0x02) == 0)
    {
        bucket++;
        if(bucket > 100)
        {
            returnVal = 0;
        }
    }

    return returnVal;
}

int __ButtonReadS3()
{
    /* Things */
}
