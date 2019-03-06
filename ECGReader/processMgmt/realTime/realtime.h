
void InitProcList()
{
    ListInit(&processList);
}
/*!
 * @brief Checks to make sure the process hasn't been overflowed and isn't NULL
 * @param proc a pointer ot the process we're verifying
 * @return true(1u) for valid, otherwise false(0u)
 */
bool CheckProcessValid(Process_t* proc)
{
    return ((proc->_overflowDetect != DETECTOVERFLOWVAL) && (proc != NULL));
}
/*!
 * @brief Tries to deal with process starvation by 
 * gradually lowering the priorty of a process until
 * Another one can take its place
 * 
 * @param proc A pointer to the process we wish to lower the priority of
 */
void DecreaseProcessPriority(Process_t* proc)
{
    proc->_priority--;
    Process_t* nextProc = LISTENTRY(proc->_item._nextItem
                                    , Process_t
                                    , _item);

    /* If priority has changed in a meaningful way, swap them */
    if(nextProc->_priority > proc->_priority)
    {
        ListItemInsert(proc, nextProc);
    }
}

/*!
 * @brief Initialises a process for running
 * @param procPriority The priority of the process
 * @param A pointer to the function
 */
void InitProcess(unsigned int procPriority
                 , void (*funct)());
/*!
 * @brief Starts the scheduler
 */
void StartRealTimeScheduler();
/*!
 * @brief services the scheduler whenever it's called
 */
void ServiceScheduler();