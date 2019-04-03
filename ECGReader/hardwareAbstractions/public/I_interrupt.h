/*!
 * @brief Public forward declarations for the timer init functions
 * @author Harrison Marcks
 * @addtogroup hardwareAbstractions
 * @addtogroup public
 * @date 10/12/18
 */

#ifndef __I_TIMER_H__
#define __I_TIMER_H__

/*!
 * @brief Initialises Timer_A0 for 1ms
 */
extern void InterruptTimerA0Init(void);
/*!
 * @brief initialises the timer_A2 for the sliders
 */
extern void InterruptTimerA2Init(void);
/*!
 * @brief initialises the UCB0 interrupt for use
 */
void InterruptUCB0Init(void);
/*!
 * @brief Disables all interrupts
 */
extern void InterruptDisable(void);
/*!
 * @brief Enables all interrupts
 */
extern void InterruptEnable(void);

#endif /* __I_TIMER_H__ */
