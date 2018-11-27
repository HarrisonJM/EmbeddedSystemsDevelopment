/*!
 * @brief eventQueue
 * @author Harrison J Marcks
 * @date 23/11/18
 */

#ifndef __EVENT_QUEUE_H__
#define __EVENT_QUEUE_H__

#include "../helpers/boollint.h"

#define SIZE_OF_EVENT_Q   8

/*!
 * @brief EVENT_T Stores details for a specific event
 */
typedef struct EVENT
{
    /*!{*/
    int event; /*! < The event type */
    int param1; /*! < The first parameter for the event  */
    int param2; /*! < The second parameter for the event */
    int param3; /*! < The third parameter for the event */
    /*!}*/
} EVENT_T;

/*! @brief typedef for allowing the struct to contain an understanding of itself within itself*/
typedef struct EVENTQUEUE EVENTQUEUE_T;
/*!
 * @brief EVENTQUEUE_T The actual queue that will hold events
 */
struct EVENTQUEUE
{
    /*!{*/
    uint32_t size; /*! < The size current of the queue. Number of elements */
    uint32_t head; /*! < The location of the head. */
    uint32_t tail; /*! < The location of the tail. */
    /*!}*/
    /*!
     * @name QueueControl
     */
    /*!{*/
    EVENT_T queue[SIZE_OF_EVENT_Q]; /*! < An array of events (The queue itself) */
    bool (*PopFront)(EVENTQUEUE_T *q,
                    EVENT_T *e); /*! < A function pointer to the Popfront function */

    bool (*PushBack)(EVENTQUEUE_T *q,
                    const EVENT_T *e); /*! < A function pointer to the PushBack function */
    /*!}*/
};
/*!
 * @brief Public declaration of the QueueInit function
 */
void QueueInit(EVENTQUEUE_T *q);


#endif /* __EVENT_QUEUE_H__ */

// Move to Timer
//struct EventQueue led_q;

