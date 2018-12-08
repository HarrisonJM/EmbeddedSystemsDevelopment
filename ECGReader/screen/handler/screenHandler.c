/*!
 * @brief direct handler for printing to the LCD screen
 * @author Huseyin Sert, Harrison Marcks
 * @date 30/11/2018
 */

#include <stdlib.h>

 #include "screen/handler/screenHandler.h"

#include "hardwareAbstractions/public/I_lcd.h"

#include "helpers/boollint.h"

#include "font8x8_basic.h"

#define CHARPIXELWIDTH 8
#define SCREENMAXX 12
#define SCREENMAXY 12

/* The display buffer we're using */
uint8_t DisplayBuffer[96][96 / CHARPIXELWIDTH];

/* Forward declarations */
static char __ReverseByte(char inByte);

/*!
 * @brief Initialise the display buffer
 * @param setting Pass in character to print across screen
 */
void ScreenDisplayBufferInit(char setting)
{
    uint8_t i; /* X */
    uint8_t j; /* char position */
    uint8_t k; /* Y */

    unsigned char ch = setting - ' ';
    for (k = SCREENMAXY; k != 0; --k)
    {
        for (i = SCREENMAXX; i != 0; --i)
        {
            for (j = CHARPIXELWIDTH; j != 0; --j)
            {
                DisplayBuffer[(k * CHARPIXELWIDTH) + j][i] = __ReverseByte(font8x8_basic[ch][j]);
            }
        }
    }
}
/*!
 * @brief Sets the display buffer to contain a single char in the given position
 * @param x The pixel column we wish to print to (Actual number, 0->LCDPIXELMAXX)
 * @param y The row we wish to print to (in pixel location 0->LCDPIXELMAXY
 * @param ch The character we wish to print
 * @param invert Whether to invert the text colour (true for black background/white text)
 */
void ScreenPrintChar(uint8_t x
                     , uint8_t y
                     , const char ch
                     , bool invert)
{
    uint8_t i = CHARPIXELWIDTH - 1; /* Character byte iterator */
    char chActual = 0;
    /* Assign char to array value */
    chActual = ch - ' ';

    for(i = 0; (i < CHARPIXELWIDTH); ++i)
    {
            DisplayBuffer[y + i][x] = __ReverseByte(font8x8_basic[chActual][i]);
    }
}
/*!
 * @brief Writes pixels to where they are wanted on the screen to the displayBuffer
 * @param x The column to start printing, in pixels (multiples of 8)
 * @param y The row to start printing, in pixels (multiples of 8)
 * @param str_p The string we wish to print
 * @param invert true to invert text (black background)
 */
void ScreenSetText(uint8_t x
                   , uint8_t y
                   , const char* str_p
                   , bool invert)
{
    uint8_t j; /* Column by pixel iterator */
    j = 0;
    while (*str_p != '\0')
    {
        /* Print the string to the screen */
        /*! @todo Move division to RAM */
        ScreenPrintChar(((x / CHARPIXELWIDTH) + j)
                        , y
                        , (*str_p++)
                        , invert);

        j += 1; /* move to next pixel */
    }
}
/*!
 * @brief Writes lines from the top left, down the screen
 * @param str_p The string we wish to print
 * @param invert true to set background black/white text
 */
void ScreenPrint(const char* str_p
                 , bool invert)
{
    uint8_t row = 0;
    uint8_t column = 0;

    while ((*str_p) != '\0')
    {
        char ch = *str_p;
        ScreenPrintChar(column
                      , row
                      , ch
                      , invert);
        column += 1;
        str_p++;

        if ((*str_p) == '\n')
        {
            column = 0;
            row += CHARPIXELWIDTH;
            str_p++;
        }
    }
}
/*!
 * @brief Inverts the byte passed to it
 * @param inByte the char to convert
 */
static char __ReverseByte(char inByte)
{
    char outByte;

        outByte = 0;

        if ((inByte & BIT0) > 0)
            outByte |= BIT7;
        if ((inByte & BIT1) > 0)
            outByte |= BIT6;
        if ((inByte & BIT2) > 0)
            outByte |= BIT5;
        if ((inByte & BIT3) > 0)
            outByte |= BIT4;
        if ((inByte & BIT4) > 0)
            outByte |= BIT3;
        if ((inByte & BIT5) > 0)
            outByte |= BIT2;
        if ((inByte & BIT6) > 0)
            outByte |= BIT1;
        if ((inByte & BIT7) > 0)
            outByte |= BIT0;

        return outByte;
}
/*!
 * @brief Prints to the display itself
 *
 * The counting up loops are, unfortunately, required in this implementation
 * otherwise nothing appears to work.
 *
 * @todo Figure out how to change loops to counting done to improve efficiency
 * @todo remove tight loops in the while() function and instead do it using interrupts
 */
void ScreenFlushDisplayBuffer()
{
    /* line and column names are now redundant but left in just for piece of mind */
    uint32_t column = 0;
    uint32_t line = 0;
    /*! @brief Write lines (0x80, image update mode ) and VCOM bit (0x40, video communication) */
    static const uint8_t command = 0xC0;

    LCDSetCSHigh();

    LCDWriteCommandOrData(command);

    for(line = 0; line < LCDPIXELMAXX; ++line)
    {
        LCDWriteCommandOrData(__ReverseByte(line + 1));

        for(column = 0; column < SCREENMAXX; ++column)
        {
            LCDWriteCommandOrData(DisplayBuffer[line][column]);
        }
        /* EOL byte */
        LCDWriteCommandOrData(0x00);
    }

    /* End of block byte */
    LCDWriteCommandOrData(0x00);

    LCDWaitUntilDone();

    __delay_cycles(8); /* Ensure a 2us minutes delay to meet the LCD's thSCS */

    LCDSetCSLow();

}