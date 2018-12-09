#ifndef __MENU_H__
#define __MENU_H__

#include "../eventQueue/eventQueue.h"

typedef enum MENUSELECT {
    MENU_NULL,
    MENU_ECG,
    MENU_PREVREAD,
    MENU_PROFILE,
    MENU_OPTIONS,
    MENU_REBOOT
} MENUSELECT_T;

typedef struct MENUCONTEXT {
    MENUSELECT_T selectedOption;
    uint8_t textIndex;
} MENUCONTEXT_T;

const char *menuMain[SIZE_MENU_MAIN] = 
{
     "",
     " ECG",
     " PrevRd",
     " Profiles",
     " Options",
     " Reboot"
};

void MenuTimer(EVENT_T *e);

#endif /* __MENU_H__ */
