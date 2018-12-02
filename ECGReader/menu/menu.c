/*!
 * @brief Framework for displaying and navigating the menu. Selected option will load relevant code
 * @author Dan Steer
 * @author Harrison Marcks
 * @date 12/11/2018
 */

#include <screen/handler/screenHandler.h>
#include "menu.h"

MENUCONTEXT_T menu;

void MenuNull()
{
 /* Splash screen/initialization or smth */
}

void MenuECG()
{

}

void MenuPreviousReading()
{
    ScreenSetText(2,
            0,
            "> Previous"
            ,false);
}

void MenuProfile()
{
    ScreenSetText(3,
                0,
                "> Profile"
                ,false);
}

void MenuOptions()
{
    ScreenSetText(4,
            0,
            "> Options"
            ,false);
}

void MenuReboot()
{
    ScreenSetText(5,
            0,
            "> Reboot"
            ,false);
}

/*!
 * @brief Decides whether an action needs to take place
 */
void MenuTimer()
{
    /* Print all options */
    /*
     * Option selection/inversion is handled by
     * some file scoped toggleable booleans
     */
}

/*!
 * @brief Controls moving the menu to a new state
 *
 */
void MenuEnterState(MENUSELECT_T newState)
{
    switch(menu.selectedOption)
    {
    case MENU_NULL:
        break;
    case MENU_ECG:
        break;
    case MENU_PREVREAD:
        break;
    case MENU_PROFILE:
        break;
    case MENU_OPTIONS:
        break;
    case MENU_REBOOT:
        break;
    }

    menu.selectedOption = newState;
}

/*!
 * @brief load relevant activity when selected
 */
int LoadActivity(MENUSELECT_T activityToRun)
{
	return 0;
}

/*!
 * @brief navigate the menu using the buttons
 * @param menuOptions array of menu options
 * @param menuSize how many menu options to be displayed
 * @param position current position within the menu
 */
int MenuNavigate(const char **menuOptions, int menuSize, int position)
{
	/*printf("%s\n", *menuOptions);*/
	return 0;
}

/*!
 * @brief highlight the active menu option
 * @param position current position within the menu
 */
int MenuDisplaySelected(int position)
{
	return 0;
}

/*!
 * @brief push each menu option to the screen
 * @param menuOptions array of menu options
 * @param menuSize how many menu options to be displayed
 */
int MenuDisplay(const char **menuOptions, int menuSize)
{
	int position = 0;
//	int i;
//	for(i = 0; i < menuSize; i++)
//	{
//		/*printf("%s\n", menuOptions[i]);*/
//	}

	MenuDisplaySelected(position);
	MenuNavigate(menuOptions, menuSize, position);
	return 0;
}

/*!
 * @brief load menu options based on select. Main menu is loaded on system start.
 * @param option The menu of which to load options 
 */
int MenuLoad(char option[])
{
	const char **menuOptions;
	int menuSize;

	if(option == "main")
	{
		menuOptions = menuMain;
		menuSize = SIZE_MENU_MAIN;
		MenuDisplay(menuOptions, menuSize);
	}
	else
	{
		/*printf("Error: invalid option\n");*/
	}

	return 0;
}


/*!
 * @brief load default menu option (main menu)
 */
/*int MenuInit()
{
	MenuLoad("main");
	return 0;
}*/

///*!
// * @brief load default menu option (main menu)
// */
//int main()
//{
//	MenuLoad("main");
//	return 0;
//}
