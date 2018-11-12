/*!
 * @brief function pointer declarations for use throughout the program
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#ifndef __I_BUTTON_H__
#define __I_BUTTON_H__

extern void CreateButtonLinks();

int (*initButtonHardware)();
int (*ReadButtonS2)();
int (*ReadButtonS1)();

#endif /* __I_BUTTON_H__ */
