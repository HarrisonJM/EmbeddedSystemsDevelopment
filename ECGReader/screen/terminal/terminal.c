/*!
 * @brief defines the "terminal" that text/images will be sent to and handled by
 *
 * The terminal functions on a 12x12 char grid (96x96 pixels)
 *
 *
 * @author Harrison Marcks
 * @date 30/11/2018
 */

#include <screen/handler/screenHandler.h>
#include "terminal.h"
#include "../../helpers/boollint.h"
#include "../../helpers/circularBuffer/circularBuffer.h"

/* Our terminal object */
TERMINAL_T myTerm;
/* The buffer we'll be using for the circular buffer */
char linesForBuffer[MAXBUFFERSIZE*MAXLINELENGTH];

/*!
 * @brief Resets basic terminal Struct Information
 */
void TerminalBasicReset()
{
    myTerm.xCursorPos = 0;
    myTerm.yCursorPos = 0;
    myTerm.bufferLinePos = 0;
}
/*!
 * @brief initialises the terminal
 */
void TerminalInit()
{
    TerminalBasicReset();
    CircBuffInit(&(myTerm.lineBuffer),
            linesForBuffer);
}
/*!
 * @brief Sets the cursor to 0,0
 */
void TerminalReset()
{
    TerminalBasicReset();
    myTerm.lineBuffer.Reset(&(myTerm.lineBuffer));
}
/*!
 * @brief Clears the terminal i.e. sets the cursor to 0,0 and clears the screen
 */
void TerminalClear()
{
    TerminalBasicReset();
    myTerm.lineBuffer.Reset(&(myTerm.lineBuffer));

    int i = 0;

    /* 12 spaces */
    const char* clear = "            ";
    for(; i < MAXBUFFERSIZE; ++i)
    {
        ScreenSetText(0,
                      i,
                      clear,
                      false);
    }
}
/*!
 * @brief Prints to the terminal
 * @param str_p a pointer to the string we wish to print
 */
void TerminalPrint(const char* str_p)
{

}








