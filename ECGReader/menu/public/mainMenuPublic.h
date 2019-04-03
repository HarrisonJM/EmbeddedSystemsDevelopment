/*!
 * @brief Public declarations for the mainMenu Activity
 * @author Harrison Marcks
 * @date 9/12/2018
 *
 * @addtogroup menu
 * @{
 * @addtogroup public
 * @{
 */

#ifndef __MAIN_MENU_PUBLIC_H__
#define __MAIN_MENU_PUBLIC_H__

extern struct EVENT;
typedef struct EVENT EVENT_T;

/* Forward Declarations */
/*!
 * @brief Decides whether an action needs to take place
 * @param bS1Event The latest event on button S1
 * @param bS2Event The latest event on button S2
 */
extern void MainMenuTimer(EVENT_T *bS1Event,
                          EVENT_T *bS2Event);


#endif /* __MAIN_MENU_PUBLIC_H__ */

/*! @} @} */
