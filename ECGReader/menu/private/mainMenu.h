/*!
 * @brief MainMenu related definitions
 * @author Harrison Marcks
 * @date 9/12/2018
 */

#ifndef __MENU_H__
#define __MENU_H__

#include "../public/menuUtility.h"
#include "../../eventQueue/eventQueue.h"

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

/*! @brief Strings containing the available menu options to be printed. NB the leading space*/
const char *MainMenuStrings[SIZEMENUMAIN] =
{
     "",
     " ECG",
     " PrevRd",
     " Profiles",
     " Options",
     " Reboot"
};

#endif /* __MENU_H__ */
