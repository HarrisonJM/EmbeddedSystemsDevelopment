/*!
 * @brief Real Time Scheduler header
 * @author Harrison Marcks
 * @addtogroup processMgmt
 * @addtogroup realTime
 * @date 29/03/2019
 */

#ifndef __REALTIME_H__
#define __REALTIME_H__

#include <helpers/boollint.h>

/*!
 * @brief The different states a process can be in
 * @{
 */
typedef enum PROCSTAT procStat_e;
/*! @} */
/*!
 * @brief The process block
 * @{
 */
typedef struct PROCESS Process_t;
/*! @} */

void InitProcList();
/*!
 * @brief Checks to make sure the process hasn't been overflowed and isn't NULL
 * @param proc a pointer ot the process we're verifying
 * @return true(1u) for valid, otherwise false(0u)
 */
bool CheckProcessValid(Process_t* proc);
/*!
 * @brief Tries to deal with process starvation by 
 * gradually lowering the priorty of a process until
 * Another one can take its place
 * 
 * @param proc A pointer to the process we wish to lower the priority of
 */
void DecreaseProcessPriority(Process_t* proc);
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

#endif /* __REALTIME_H__ */
