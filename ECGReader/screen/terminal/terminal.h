/*!
 * @brief Terminal context header
 * @author Harrison Marcks
 * @date 30/11/2018
 */

#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include "../../helpers/circularBuffer/circularBuffer.h"

/*! @brief The maximum length a line may be */
#define MAXLINELENGTH 12

/*!
 * @brief defines our terminal object
 */
typedef struct TERMINAL{
    /*!@{*/
    CIRCULARBUFFER_T lineBuffer; /*! < The terminals line circular buffer */
    uint8_t bufferLinePos; /*! < The position the terminal is on*/
    uint8_t xCursorPos; /*! < Where the cursor is on the x-axis (column) */
    uint8_t yCursorPos; /*! < Where the cursor is on the y-axis (row) */
    /*!@}*/
}TERMINAL_T;

/*!
 * @brief Initialises our terminal
 */
void TerminalInit();

#endif /* __TERMINAL_H__ */
