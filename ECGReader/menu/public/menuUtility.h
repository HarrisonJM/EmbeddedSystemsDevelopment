/*!
 * @brief Definitions for all menu related things
 * @author Harrison Marcks
 * @date 9/12/2018
 */

#ifndef __MENU_UTILITY_H__
#define __MENU_UTILITY_H__

#include "../../helpers/boollint.h"

/*! @brief The context for the menu that We're dealing with */
typedef struct MENUCONTEXT {
    /*!@{*/
    int selectedOption;             /* < The currently selected option */
    uint8_t textIndex;              /* < The index for address dealing with how to change the text */
    bool selected;                  /* < Whether the menu is currently delving into an activity/suboption */
    /*!@}*/
} MENUCONTEXT_T;

#endif /* __MENU_UTILITY_H__ */
