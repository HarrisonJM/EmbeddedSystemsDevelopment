/*!
 * @brief Framework for displaying and navigating the menu. Selected option will load relevant code
 * @author Dan Steer
 * @author Harrison Marcks
 * @date 12/11/2018
 */

#include <screen/handler/screenHandler.h>
#include "menu.h"

/*! Pre-processor Macros */
#define SIZE_MENU_MAIN 6 /*! < The size of the Menu */

/* Prototypes */
void MenuEnter();

/* File scope variables */
static MENUCONTEXT_T menu;

/* Definitions */
void MenuNull()
{
 /* Splash screen/initialization or smth */

    menu.selectedOption = MENU_ECG;
}
/*!
 * @brief Prints the menu to the screen, with the selected option
 */
void MenuEnter()
{
    bool invert = false;
    int i = 0;
    for(i = 0; i < SIZE_MENU_MAIN; ++i)
    {
        if ( i == menu.textIndex)
        {
            invert = true;
        }
        ScreenSetText(0, i*SCREENMAXY, *(menuMain+i), invert);
        invert = false;
    }
    ScreenFlushDisplayBuffer();
}
/*!
 * @brief Decides whether an action needs to take place
 */
void MenuTimer(EVENT_T *bS1Event, EVENT_T *bS2Event)
{
    /* Left button, next option */
    if(bS1Event->event == EVENT_BUTTON_PRESSED)
    {
        MenuEnterState(menu.selectedOption+1);
    }
    /* Right button, select activity */
    else if(bS1Event->event == EVENT_BUTTON_PRESSED)
    {
        LoadActivity
    }
}
/*!
 * @brief Controls moving the menu to a new state
 * @param newState The state the menu should take
 */
void MenuEnterState(MENUSELECT_T newState)
{
    switch(newState)
    {
    case MENU_NULL:
        menu.textIndex = 0;
        break;
    case MENU_ECG:
        menu.textIndex = 1;
        break;
    case MENU_PREVREAD:
        menu.textIndex = 2;
        break;
    case MENU_PROFILE:
        menu.textIndex = 3;
        break;
    case MENU_OPTIONS:
        menu.textIndex = 4;
        break;
    case MENU_REBOOT:
        menu.textIndex = 5;
        break;
    }

    MenuEnter();
    menu.selectedOption = newState;
}
/*!
 * @brief load relevant activity when selected
 */
int MenuLoadActivity()
{
    switch(newState)
    {
    case MENU_NULL:
        /* Shouldn't ever be here */
        break;
    case MENU_ECG:
        /* Open the ECG activity. Which should probably be a tight loop */
        break;
    case MENU_PREVREAD:
        /* Open the Previous reads activity. Goes to another menu that let's you select previous read dates, then just replays the results */
        break;
    case MENU_PROFILE:
        /* Loads another menu that lets you select users and new users, etc*/
        break;
    case MENU_OPTIONS:
        /* Goes to the options menu*/
        break;
    case MENU_REBOOT:
        /* Reboots the machine */
        break;
    }
}
