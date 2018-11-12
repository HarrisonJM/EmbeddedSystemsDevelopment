/*!
 * @brief Framework for displaying and navigating the menu. Selected option will load relevant code
 * @author Dan Steer
 * @date 12/11/2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

/*!
 * @brief load relevant activity when selected
 */
int LoadActivity()
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
	for(int i = 0; i < menuSize; i++)
	{
		/*printf("%s\n", menuOptions[i]);*/
	}
	
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
int main()
{
	MenuLoad("main");
	return 0;
}