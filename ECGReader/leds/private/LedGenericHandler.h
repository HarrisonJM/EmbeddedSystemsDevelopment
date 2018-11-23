/*!
 * @brief Header for generic handler
 * @author Harrison J Marcks
 * @date 23/11/18
 */

#ifndef __LEDGENERICHANDLER_H__
#define __LEDGENERICHANDLER_H__

void LEDStoreInit(LEDSTORE_T* ledStore);
LEDSTATE_T __LEDGetState(LEDSTORE_T *ledStore);
void __LEDHandler(LEDSTORE_T* ledStore,
                  BUTTONSELECT_T button);

#endif /* __LEDGENERICHANDLER_H__ */
