/*!
 * @brief declares public interface to the circular buffer
 * @author Harrison Marcks
 * @date 30/11/2018
 */

#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <stdlib.h>
#include "../boollint.h"

/*! @brief Hard-limit on the size of the buffer */
#define MAXBUFFERSIZE 32
/*! @brief pre-typedef declaration for struct */
typedef struct CIRCULARBUFFER CIRCULARBUFFER_T;
/*!
 * @brief defines the structure used for circular buffers
 */
struct CIRCULARBUFFER {
    /*!@{*/
    void* __buffer; /* < The buffer itself holding pointers to locations */
    size_t __head; /* < The buffer's head */
    size_t __tail; /* < The buffer's tail*/
    bool __full; /* < Is the buffer fool flag */
    /*!@}*/
    /*!
     * @name functionPointers
     */
    /*!@{*/
    void (*Reset)(CIRCULARBUFFER_T* circBuff);
    void (*PushHard)(CIRCULARBUFFER_T* circBuff
                     , const void* data
                     , size_t dataSizeBytes);
    int (*PushSoft)(CIRCULARBUFFER_T* circBuff
                    , const void* data
                    , size_t dataSizeBytes);
    int (*Get)(CIRCULARBUFFER_T* circBuff
               , void* data
               , size_t dataSizeBytes);
    bool (*Empty)(CIRCULARBUFFER_T* circBuff);
    bool (*Full)(CIRCULARBUFFER_T* circBuff);
    size_t (*Size)(CIRCULARBUFFER_T* circBuff);
    /*!@}*/
};
/*!
 * @brief Initialises a CIRCULARBUFFER_T
 * @param circBuff A pointer to the circular buffer who's pointer we wish to advance
 * @param buffer A pointer to where the alocated buffer is
 */
void CircBuffInit(CIRCULARBUFFER_T* circBuff
                   , void* buffer);

#endif /* __CIRCULAR_BUFFER_H__ */
