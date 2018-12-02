/*!
 * @brief contains definitions for the circular buffer
 * @author Harrison J Marcks
 * @date 30/11/2018
 */

#include "../boollint.h"
#include "circularBuffer.h"

/*!
 * @brief Advances the head and tail pointer in the circular buffer
 * @param circBuff A pointer to the circular buffer who's pointer we wish to advance
 */
static void __CircBuffAdvancePointer(CIRCULARBUFFER_T* circBuff)
{
    if(circBuff->Full)
    {
        /*! @todo Move to memory as per other todo */
        circBuff->__tail = (circBuff->__tail + 1) % MAXBUFFERSIZE;
    }

    /* Modulo resets the head and tail to 0 so that it can repeat*/
    /*! @todo Move to memory as per other todo */
    circBuff->__head = (circBuff->__head + 1) % MAXBUFFERSIZE;
    /* Check if full */
    circBuff->__full = (circBuff->__head == circBuff->__tail);

}
/*!
 * @brief retreats the head/tail pointer in the circular buffer
 * @param circBuff A pointer to the circular buffer who's pointer we wish to advance
 */
static void __CircBuffRetreatPointer(CIRCULARBUFFER_T* circBuff)
{
    circBuff->__full = false;
    /*! @todo Move to memory as per other todo */
    circBuff->__tail = (circBuff->__tail +1) % MAXBUFFERSIZE;
}
/*!
 * @brief Resets the pointer to zero in the circular buffer
 * @param circBuff A pointer to the circular buffer who's pointer we wish to advance
 */
static void __CircBuffReset(CIRCULARBUFFER_T* circBuff)
{
    circBuff->__full = false;
    circBuff->__head = 0;
    circBuff->__tail = 0;
}
/*!
 * @brief Pushes new data onto the buffer, standard use case, overwrites oldest data
 * @param circBuff A pointer to the circular buffer who's pointer we wish to advance
 * @param data A pointer to the data we are pushing on
 * @param dataSizeBytes The size of the data we're pusing
 */
static void __CircBuffPushHard(CIRCULARBUFFER_T* circBuff
                      , const void* data
                      , size_t dataSizeBytes)
{
    void *mcRet = memcpy(((circBuff->__buffer)+circBuff->__head)
                       , data
                       , dataSizeBytes);

    if(mcRet != NULL)
    {
        __CircBuffAdvancePointer(circBuff);
    }
}
/*!
 * @brief Pushes new data onto the buffer provided there is space
 * @param circBuff A pointer to the circular buffer who's pointer we wish to advance
 * @param data A pointer to where the new data is
 * @param dataSizeBytes The size fo the data we're pushing
 * @return 0 for success
 */
static int __CircBuffPushSoft(CIRCULARBUFFER_T* circBuff
                     , const void* data
                     , size_t dataSizeBytes)
{
    int retCode = 1;

    if(!circBuff->Full(circBuff))
    {
        int* mcRet = memcpy((circBuff->__buffer)+circBuff->__head
                           , data
                           , dataSizeBytes);
        if(mcRet != NULL)
        {
            __CircBuffAdvancePointer(circBuff);
            retCode = 0;
        }
        else
        {
            retCode = 1;
        }

        retCode = 0;
    }

    return retCode;
}
/*!
 * @brief Gets the data pointed to by the tail of the buffer
 * @param circBuff A pointer to the circular buffer who's pointer we wish to advance
 * @param data A pointer to where to store the data
 * @param dataSizeBytes The size of the data we're getting
 * @return 0 for success
 */
static int __CircBuffGet(CIRCULARBUFFER_T* circBuff
                          , void* data
                          , size_t dataSizeBytes)
{
    int retCode = 1;

    if(!circBuff->Empty(circBuff))
    {
        int* mcRet = memcpy(data
                            , (circBuff->__buffer)+circBuff->__tail
                            , dataSizeBytes);

        if(mcRet != NULL)
        {
            __CircBufffRetreatPointer(circBuff);
            retCode = 0;
        }
        else
        {
            retCode = 1;
        }
    }

    return retCode;
}
/*!
 * @brief Returns whether the buffer is indeed empty (using the full flag)
 * @param circBuff A pointer to the circular buffer who's pointer we wish to advance
 * @return 'true' if empty
 */
static bool __CircBuffEmpty(CIRCULARBUFFER_T* circBuff)
{
    return (!circBuff->__full && (circBuff->__head == circBuff->__tail));
}
/*!
 * @brief Returns the stored full flag for the buffer
 * @param circBuff A pointer to the circular buffer who's pointer we wish to advance
 * @return 'true' if full
 */
static bool __CircBuffFull(CIRCULARBUFFER_T* circBuff)
{
    return circBuff->__full;
}
/*!
 * @brief Returns the current "size" of the buffer
 * @param circBuff A pointer to the circular buffer who's pointer we wish to advance
 * @return The size of the buffer
 */
static size_t __CircBuffSize(CIRCULARBUFFER_T* circBuff)
{
    size_t size = MAXBUFFERSIZE;

    /* If it _isn't_ full */
    if(!circBuff->__full)
    {
        if(circBuff->__head >= circBuff->__tail)
        {
            /* Just minus the tail from the head if the head is past the tail */
            size = circBuff->__head - circBuff->__tail;
        }
        else
        {
            /* If it isn't, take the result from the maximum __buffer size */
            size = (MAXBUFFERSIZE + (circBuff->__head - circBuff->__tail));
        }
    }

    return size ;
}
/*!
 * @brief Public circular buffer init function
 * @param circBuff A pointer to the circular buffer who's pointer we wish to advance
 * @param buffer A pointer to where the alocated buffer is
 */
void CircBuffInit(CIRCULARBUFFER_T* circBuff,
                   void* buffer)
{
    circBuff->Reset = __CircBuffReset;
    circBuff->PushHard = __CircBuffPushHard;
    circBuff->PushSoft = __CircBuffPushSoft;
    circBuff->Get = __CircBuffGet;
    circBuff->Empty = __CircBuffEmpty;
    circBuff->Full = __CircBuffFull;
    circBuff->Size = __CircBuffSize;

    circBuff->__buffer = buffer;

    circBuff->Reset(circBuff);
}
