/*!
 * @brief LED Link header for function pointers
 * @author Harrison J Marcks
 * @date 12/11/18
 */

#ifndef __I_LEDS_H__
#define __I_LEDS_H__

extern void CreateLEDLinks();

void (*LEDOnGreen)();
void (*LEDOffGreen)();
void (*LEDToggleGreen)();

void (*LEDOnRed)();
void (*LEDOffRed)();
void (*LEDToggleRed)();

#endif /* __I_LEDS_H__ */
