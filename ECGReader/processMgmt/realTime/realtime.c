/*!
 * @brief realtime scheduler (process priorites)
 * 
 * @author harrison marcks
 * 
 * @date 4/3/2019
 * 
 * @todo delay
 * @todo idle process
 * @todo process starvation
 */
#include <msp430fr5969.h>

#include "realtime.h"

#include <helpers/linkedlist/linkedList.h>
#include <helpers/boollint.h>

/*! Maximum number of processes we want */
#define MAXPROC 100
/*! Maximum stack size */
#define STACKSIZE 100
/*! Arbitrary number to check for overflow */
#define DETECTOVERFLOWVAL (uint32_t)0xcd6abf4b
/*!
 * @brief The different states a process can be in
 * @{
 */
 enum PROCSTAT {
    TASK_UNUSED,
    TASK_RUNNABLE,
    TASK_RUNNING,
    TASK_WAITING,
    TASK_BLOCKED
};
/*! @} */

 /*!
  * @brief File scoped variables
  * These must be declared outside of the function scope otherwise the
  * assembler can't find the addresses (because they don't exist)
  * @{
  */
/* static */LONG intStat;        /*! <  Status flags */
 /* static */LONG stackPointer;   /*! <  Stackpointer tracker */
 /* static */LONG progCount;      /*! <  The program counter */
 /* static */LONG savedSP;        /*! <  Another stackpointer tracker */
 /* static */WORD pc1;            /*! <  First part of program counter and status register combination */
 /* static */WORD pc2;            /*! <  PC&SR shifted */
/*! @}*/

/*!
 * @brief The process block
 * @{
 */
struct PROCESS {
    uint16_t _procStat;          /*! < The status of the process */
	uint16_t _milliDelay;        /*! < */
	uint32_t _sp;                /*! < The stack pointer */
    uint8_t _index;              /*! < Where in the process list the process sits */
    bool _inUse;                 /*! < Whether this block is in use */
    int8_t _priority;            /*! < Where in the process list the process sits */
    int8_t _origPriority;        /*! < The processes original priority. Used to deal with aging/starvation */
    linkedListItem_T _item;      /*! < The list element identifier */
	uint8_t _stack[STACKSIZE];   /*! < The stack */

    uint32_t _overflowDetect; /*! < Shoudl help to detect if there is overflow */
};
/*! @} */

/* Forward Declarations */
static void PriorityInsertNewProcess(Process_t* newProcess);
static Process_t* FindFreeProcessBloc();

/* Filescoped */
/* An array of all the available processes (Empty) */
static Process_t processes[MAXPROC] = {0};
/* The list of processes */
static linkedList_T processList = {0};
/* Tracks the current/head running process */
static Process_t* currentlyRunningProcess = NULL;

/*!
 * @brief initialises the Processor list and process blocks
 */
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
void __DecreaseProcessPriority(Process_t* proc)
{
    proc->_priority--;
    Process_t* nextProc = LISTENTRY(proc->_item._nextItem
                                    , Process_t
                                    , _item);

    /* If priority has changed in a meaningful way, swap them */
    if(nextProc->_priority > proc->_priority)
    {
        ListItemInsert(&proc->_item
                        , &nextProc->_item);
    }
}
/*!
 * @brief Tries to deal with process starvation by 
 * gradually increasing the priorty of a process until
 * it's run
 * 
 * @param proc A pointer to the process we wish to increase the priority of
 */
void __IncreaseProcessPriority(Process_t* proc)
{
    proc->_priority++;
    Process_t* nextProc = LISTENTRY(proc->_item._nextItem
                                    , Process_t
                                    , _item);

    /* If priority has changed in a meaningful way, swap them */
    if(nextProc->_priority < proc->_priority)
    {
        ListItemInsert(&proc->_item
                        , &nextProc->_item);
    }
}

/*!
 * @brief More public function for specifically increasing the 
 * _current_ process's priority
 */
void IncreasePriority()
{
    __IncreaseProcessPriority(currentlyRunningProcess);
}
/*!
 * @brief More public function for specifically decreasing the 
 * _current_ process's priority
 */
void DecreasePriority()
{
    __DecreaseProcessPriority(currentlyRunningProcess);
}
/*!
 * @brief Delays the current process for msDelay
 * @param msDelay a 16-bit number for hwo many milliseconds 
 * the process should eb delayed for
 */
void AddDelay(uint16_t msDelay)
{
	asm(
			" dint \n"
	        " nop \n"
	);

	// Set up the delay
    Process_t* curProc = currentlyRunningProcess;

    curProc->_milliDelay = msDelay;
    curProc->_procStat = TASK_WAITING;

	asm(
	        " nop \n"
			" eint \n"
	        " nop \n"
	);
	/* Invoke the timer as it will handle process switching */
	TA0CTL |= TAIFG;
	/* Wait for the interrupt */
	asm(
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
			" nop \n"
	);
}

/*!
 * @brief Initialises a process for running
 * @param procPriority The priority of the process
 * @param A pointer to the function
 */
void InitProcess(unsigned int procPriority
                 , void (*funct)())
{
    Process_t* newProcess = FindFreeProcessBloc();

	if (newProcess != NULL)
	{
		asm(
				" movx.a sr,&intStat\n"
			);

		intStat |= GIE;
		stackPointer = (LONG)&processes[newProcess->_index] + STACKSIZE - 2;
		progCount = (LONG)funct;

		// Construct combined PC+SR used by interrupt
		pc1 = (WORD)progCount;
		pc2 = (WORD)(((progCount>>4)&0x0F000) | intStat&0x00FFF);

		asm(
				" movx.a sp,&savedSP\n"
				" movx.a &stackPointer,sp\n"
				" push.w &pc1\n"
				" push.w &pc2\n"
				" push.a #0\n"
				" push.a #0\n"
				" push.a #0\n"
				" push.a #0\n"
				" push.a #0\n"
				" push.a #0\n"
				" push.a #0\n"
				" push.a #0\n"
				" push.a #0\n"
				" push.a #0\n"
				" push.a #0\n"
				" push.a #0\n"
				" push.a #0\n"
				" movx.a sp,&stackPointer\n"
				" movx.a &savedSP,sp\n"
			);

        newProcess->_sp = stackPointer;
        newProcess->_procStat = TASK_RUNNABLE;
		newProcess->_milliDelay = 0;
        newProcess->_priority = procPriority;

        PriorityInsertNewProcess(newProcess);
	}
}
/*!
 * @brief Starts the scheduler
 */
void StartRealTimeScheduler()
{
    /* Check proclist isn't empty */
	if (ListHead(&processList) != ListTail(&processList))
	{
        LONG stackPointer;

        Process_t* curProc = LISTENTRY(ListHead(&processList)
                                      , Process_t
                                      , _item);

        if(!CheckProcessValid(curProc))
            return;

        currentlyRunningProcess = curProc;
        curProc->_procStat = TASK_RUNNING;

		stackPointer = curProc->_sp;
		asm(
				" movx.a &stackPointer,SP \n"
				" pop.a R3 \n"
				" pop.a R4 \n"
				" pop.a R5 \n"
				" pop.a R6 \n"
				" pop.a R7 \n"
				" pop.a R8 \n"
				" pop.a R9 \n"
				" pop.a R10 \n"
				" pop.a R11 \n"
				" pop.a R12 \n"
				" pop.a R13 \n"
				" pop.a R14 \n"
				" pop.a R15 \n"
				" RETI \n"
		);
	}
}
/*!
 * @brief Services the scheduler whenever it's called
 */
void ServiceScheduler()
{
    LONG stackPointer;
    int i = 0;
    Process_t* nProc = NULL;
    linkedListItem_T* iProcL = NULL;

    Process_t* proc = LISTENTRY((ListHead(&processList))
                                , Process_t
                                , _item);

    /* Save first process details */
    asm(
            " push.a R15\n"
            " push.a R14\n"
            " push.a R13\n"
            " push.a R12\n"
            " push.a R11\n"
            " push.a R10\n"
            " push.a R9\n"
            " push.a R8\n"
            " push.a R7\n"
            " push.a R6\n"
            " push.a R5\n"
            " push.a R4\n"
            " push.a R3\n"
            " movx.a sp,&stackPointer\n"
        );
    proc->_sp = stackPointer;

    /* Decrement delay timers */
    iProcL = ListTail(&processList);
    while((iProcL = iProcL->_previousItem))
    {
        Process_t* iproc = LISTENTRY(iProcL
                                    , Process_t
                                    , _item);

        if (iproc->_procStat == TASK_WAITING)
        {
            if (iproc->_milliDelay > 0)
            {
                iproc->_milliDelay--;
            }

            if (iproc->_milliDelay == 0)
            {
                iproc->_milliDelay = TASK_RUNNABLE;
            }
        }
    }
    /* Switch processes (highest priority is process 0) - real-time dispatcher */
    iProcL = ListTail(&processList);
    while((iProcL = iProcL->_previousItem))
    {
        Process_t* iProc = LISTENTRY(iProcL
                                    , Process_t
                                    , _item);

        if (iProc->_procStat == TASK_RUNNABLE)
        {
            // currentlyRunningProcess = i;
            currentlyRunningProcess = iProc;
            break;
        }
    }

    nProc = LISTENTRY((ListHead(&processList))
                            , Process_t
                            , _item);
    stackPointer = nProc->_sp;

    asm(
            " movx.a &stackPointer,sp \n"
            " pop.a R3 \n"
            " pop.a R4 \n"
            " pop.a R5 \n"
            " pop.a R6 \n"
            " pop.a R7 \n"
            " pop.a R8 \n"
            " pop.a R9 \n"
            " pop.a R10 \n"
            " pop.a R11 \n"
            " pop.a R12 \n"
            " pop.a R13 \n"
            " pop.a R14 \n"
            " pop.a R15 \n"
    );
}
/*!
* @brief Returns the first available processbloc
* @return A pointer to the available bloc
*/
static Process_t* FindFreeProcessBloc()
{
    int i = MAXPROC-1;
    for(; i >= 0; --i)
    {
        if(!processes[i]._inUse)
        {
            processes[i]._index = i;
            processes[i]._overflowDetect = DETECTOVERFLOWVAL;
            return &processes[i];
        }
    }
    return NULL;
}
/*!
* @brief Inserts the new process based on its priority
* @param newProcess A pointer to the process we wish to insert
*/
static void PriorityInsertNewProcess(Process_t* newProcess)
{
    linkedListItem_T* listHead = ListHead(&processList);
    linkedListItem_T* curItem = ListTail(&processList);

    while((curItem = ListItemPrev(curItem)) != listHead)
    {
        // Search through processes for where to insert new process
        Process_t* curProc = LISTENTRY(curItem
                                        , Process_t
                                        , _item);

        // If a higher priority, we move on. 
        // If the same or lower, place here
        if (newProcess->_priority == curProc->_priority)
        {
            ListItemInsert(curItem
                            , &newProcess->_item);
        }
        else if(newProcess->_priority < curProc->_priority)
        {
            ListItemInsert(ListTail(&processList)
                            , &newProcess->_item);
        }
    }
}
