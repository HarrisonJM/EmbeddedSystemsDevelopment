/*!
 * @brief Framework for displaying and navigating the menu. Selected option will load relevant code
 * @author Dan Steer
 * @author Harrison Marcks
 * @date 12/11/2018
 */

#include "mainMenu.h"
#include "../activities/activites.h"

#include <screen/handler/screenHandler.h>
#include "buttons/buttonHandlingUtility.h"

//#include

/* Prototypes */
void MainMenuEnterState(MENUSELECT_T newState);
void MainMenuEnterActivity();
void MainMenuTimerActivity();

/* File scope variables */
static MENUCONTEXT_T menu;
/*! @brief Strings containing the available menu options to be printed. NB the leading space*/
static const char *MainMenuStrings[SIZEMENUMAIN] =
{
     "",
     " ECG",
     " PrevRd",
     " Profiles",
     " Options",
     " Reboot"
};
/* Function definitions */
/*!
 * @brief Changes the menu state to the next one
 */
MENUSELECT_T __MainMenuGoToNextOption(MENUSELECT_T oldState)
{
    MENUSELECT_T retState = MENU_NULL;
    switch(oldState)
    {
    case MENU_NULL:
        retState = MENU_ECG;
        break;
    case MENU_ECG:
        retState = MENU_PREVREAD;
        break;
    case MENU_PREVREAD:
        retState = MENU_PROFILE;
        break;
    case MENU_PROFILE:
        retState = MENU_OPTIONS;
        break;
    case MENU_OPTIONS:
        retState = MENU_REBOOT;
        break;
    case MENU_REBOOT:
        retState = MENU_ECG;
        break;
    }

    return retState;
}
/*!
 * @brief
 */
void MainMenuNull()
{
    /* Splash screen/initialization or smth */
    /* Wait a second */
    /* Then go into our first state */
    MainMenuEnterState(__MainMenuGoToNextOption(menu.selectedOption));
}
/*!
 * @brief Prints the menu to the screen, with the selected option
 */
void MainMenuEnter()
{
    bool invert = false;
    int i = 0;
    for(i = 0; i < SIZEMENUMAIN; ++i)
    {
        if ( i == menu.textIndex)
        {
            invert = true;
        }
        ScreenSetText(0, i*SCREENMAXY, *(MainMenuStrings+i), invert);
        invert = false;
    }
    ScreenFlushDisplayBuffer();
}
/*!
 * @brief Decides whether an action needs to take place
 * @param bS1Event The latest event on button S1
 * @param bS1Event The latest event on button S2
 */
void MainMenuTimer(EVENT_T *bS1Event, EVENT_T *bS2Event)
{
    if(menu.selected == false)
    {
        /* Left button, next option */
        if(bS1Event->event == EVENT_BUTTON_PRESSED)
        {
            MainMenuEnterState(__MainMenuGoToNextOption(menu.selectedOption));
        }
        /* Right button, select activity */
        else if(bS1Event->event == EVENT_BUTTON_PRESSED)
        {
            MainMenuEnterActivity();
        }
        /* Just display the scene */
        else
        {
            MainMenuEnter();
        }
    }
    else
    {
        MainMenuTimerActivity();
    }
}
/*!
 * @brief Controls moving the menu to a new state
 * @param newState The state the menu should take
 */
void MainMenuEnterState(MENUSELECT_T newState)
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

    menu.selectedOption = newState;
}
/*!
 * @brief Load relevant activity when selected
 */
void MainMenuEnterActivity()
{
    switch(menu.selectedOption)
    {
    case MENU_NULL:
        /* Shouldn't ever be here */
        break;
    case MENU_ECG:
        /* Open the ECG activity. */
        ActivityECGEnter();
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
/*!
 * @brief Enter the relevant activity's timer
 */
void MainMenuTimerActivity()
{
    switch(menu.selectedOption)
    {
    case MENU_NULL:
        /* Shouldn't ever be here */
        break;
    case MENU_ECG:
        /* Open the ECG activity. */
        ActivityECGTimer();
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
