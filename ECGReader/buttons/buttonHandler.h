/*!
 * @brief Public declarations for the button handler
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#ifndef __BUTTON_HANDLER_H__
#define __BUTTON_HANDLER_H__

void InitButtonHandler();

extern ButtonS1Timer();
extern BUTTONSTATE_E GetButtonS1State();
extern int GetButtonS1NumberOfPresses();
extern void SetButtonS1NumberOfPresses(int newPresses);

extern ButtonS2Timer();
extern BUTTONSTATE_E GetButtonS2State();
extern int GetButtonS2NumberOfPresses();
extern void SetButtonS2NumberOfPresses(int newPresses);

#endif /* __BUTTON_HANDLER_H__ */
