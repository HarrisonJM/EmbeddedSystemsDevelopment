/*!
 * @brief MainMenu related definitions
 * @author Harrison Marcks
 * @date 9/12/2018
 *
 * @addtogroup menu
 * @{
 * @addtogroup private
 * @{
 */

#ifndef __MENU_H__
#define __MENU_H__

#include "../../helpers/eventQueue/eventQueue.h"
#include "../public/menuUtility.h"

#define SIZEMENUMAIN 6 /*! < The size of the Menu */

/*! @brief Menu states, each enum represents a selection */
typedef enum MENUSELECT {
    /*!@{*/
    MENU_NULL,      /* < Null initialisation state  */
    MENU_ECG,       /* < ECG activity               */
    MENU_PREVREAD,  /* < Previous reading activity  */
    MENU_PROFILE,   /* < User profile Activity      */
    MENU_OPTIONS,   /* < Board options              */
    MENU_REBOOT     /* < Reboot the board           */
    /*!@}*/
} MENUSELECT_T;

#endif /* __MENU_H__ */

/*! @} @} */
