/*!
 * @brief Framework for displaying and navigating the menu. Selected option will load relevant code
 * @author Dan Steer
 * @author Harrison Marcks
 * @date 12/11/2018
 */

#include "mainMenu.h"
#include <screen/handler/screenHandler.h>
#include "buttons/buttonHandlingUtility.h"

/* Prototypes */
void MainMenuEnterState(MENUSELECT_T newState);
void MainMenuEnterActivity();
void MainMenuTimerActivity();

/* File scope variables */
static MENUCONTEXT_T menu;

/* Function definitions */
void MainMenuNull()
{
    /* Splash screen/initialization or smth */
    menu.selectedOption = MENU_ECG;
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
            MainMenuEnterState(menu.selectedOption++);
        }
        /* Right button, select activity */
        else if(bS1Event->event == EVENT_BUTTON_PRESSED)
        {
            MainMenuEnterActivity();
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

    MainMenuEnterActivity();
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
