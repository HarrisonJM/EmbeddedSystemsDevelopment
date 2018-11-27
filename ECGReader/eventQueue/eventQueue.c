/*!
 * @brief Implementation of event queue
 * @author Harrison J Marcks
 * @date 24/11/18
 */

#include "helpers/boollint.h"
#include "eventQueue.h"

#define EVENT_NULL      0
#define EVENT_BUTTON_PRESS  1

/*
 * Protoypes
 */
bool __PopFront(EVENTQUEUE_T *q, EVENT_T *e);
bool __PushBack(EVENTQUEUE_T* q,
                const EVENT_T *e);
/*!
 * @brief initialises the eventQueue
 * @param q A pointer to the event queue we wish to init.
 */
void QueueInit(EVENTQUEUE_T* q)
{
    q->head = 0;
    q->tail = 0;
    q->size = 0;
    q->PopFront = __PopFront;
    q->PushBack = __PushBack;
}
/*!
 * @brief reads the head of the Queue
 * @param q A pointer to the event queue we're checking
 * @param e A pointer to the event we want
 * @return TRUE if successful, otherwise FALSE
 */
bool __PopFront(EVENTQUEUE_T* q,
                      EVENT_T* e)
{
    bool returnCode;
    uint32_t head;
    uint32_t size;

    returnCode = FALSE;

    size = q->size;

    if (size > 0)
    {
        head = q->head;
        e->event = q->queue[head].event;
        e->param1 = q->queue[head].param1;
        e->param2 = q->queue[head].param2;
        e->param3 = q->queue[head].param3;

        /*! @todo Move to RAM to improve power/processing efficency
         * http://processors.wiki.ti.com/index.php/Compiler/diagnostic_messages/MSP430/1530#
         */
        head = (head + 1) % SIZE_OF_EVENT_Q;

        size--;
        q->head = head;
        q->size = size;
        returnCode = TRUE;
    }

    return returnCode;
}
/*!
 * @brief Write a new event to the Queue
 * @param q A pointer to the event queue we're checking
 * @param e The event we want to add to the queue
 * @return TRUE if successful, otherwise FALSE
 */
bool __PushBack(EVENTQUEUE_T* q,
                const EVENT_T *e)
{
    bool returnCode;
    uint32_t tail;
    uint32_t size;

    returnCode = FALSE;

    size = q->size;

    if (size < SIZE_OF_EVENT_Q)
    {
        tail = q->tail;
        q->queue[tail].event = e->event;
        q->queue[tail].param1 = e->param1;
        q->queue[tail].param2 = e->param2;
        q->queue[tail].param3 = e->param3;

        tail = (tail + 1) % SIZE_OF_EVENT_Q;
        size++;
        q->tail = tail;
        q->size = size;
        returnCode = TRUE;
    }

    return returnCode;
}
