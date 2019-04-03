/*!
 * @brief Public Forward decalrations for the watchdgo timer
 * @author Harrison Marcks
 * @addtogroup hardwareAbstractions
 * @addtogroup public
 * @date 10/12/18
 */

#ifndef __I_WATCHDOG_H__
#define __I_WATCHDOG_H__

/*!
 * @brief stops the watchdog timer
 */
extern void WatchdogStop(void);
/*!
 * @brief enables the watchdog timer
 */
extern void WatchDogEnable(void);

#endif /* __I_WATCHDOG_H__ */
