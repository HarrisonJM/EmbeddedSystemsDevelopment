/*!
 * @brief Public forward declarations for the timer init functions
 * @author Harrison Marcks
 * @addtogroup hardwareAbstractions
 * @addtogroup public
 * @date 10/12/18
 */

#ifndef __I_TIMER_H__
#define __I_TIMER_H__

extern void InterruptTimerA0Init(void);
extern void InterruptTimerA2Init(void);
/*!
 * @brief initialises the UCB0 interrupt for use
 */
void InterruptUCB0Init(void);
extern void InterruptDisable(void);
extern void InterruptEnable(void);

#endif /* __I_TIMER_H__ */
