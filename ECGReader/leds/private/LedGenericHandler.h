/*!
 * @brief Header for generic handler
 * @author Harrison J Marcks
 * @date 23/11/18
 *
 * @addtogroup leds
 * @{
 * @addtogroup private
 * @{
 */

#ifndef __LEDGENERICHANDLER_H__
#define __LEDGENERICHANDLER_H__

void LEDStoreInit(LEDSTORE_T* ledStore);
LEDACTION_T __LEDGetState(LEDSTORE_T *ledStore);
void __LEDHandler(LEDSTORE_T* ledStore);

#endif /* __LEDGENERICHANDLER_H__ */

/*! @} @} */
