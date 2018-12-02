#ifndef __MENU_H__
#define __MENU_H__

#define SIZE_MENU_MAIN 6

typedef enum MENUSELECT {
    MENU_NULL = 0X00,
    MENU_ECG = 0x01,
    MENU_PREVREAD = 0x02,
    MENU_PROFILE = 0x04,
    MENU_OPTIONS = 0x08,
    MENU_REBOOT = 0x10
} MENUSELECT_T;

typedef struct MENUCONTEXT {
    MENUSELECT_T selectedOption;
} MENUCONTEXT_T;

const char *menuMain[SIZE_MENU_MAIN] = 
{
     "",
     ">ECG",
     ">PrevRd",
     ">Profiles",
     ">Options",
     ">Reboot"
};


#endif /* __MENU_H__ */
