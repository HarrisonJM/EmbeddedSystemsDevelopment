/*!
 * @brief Definitions for lowlevel screen handling functions
 * @author Huseyin Sert, Harrison Marcks
 * @date 10/12/2018
 */

#include "../screenHandlerUtility.h"

#include "helpers/boollint.h"
#include "hardwareAbstractions/public/I_lcd.h"

#include "font8x8Basic.h"

/*!
 * @brief Initialise the display buffer
 * @param setting Pass in character to print across screen
 */
void __ScreenDisplayBufferInit(char setting,
                               uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX])
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
                DB_a[(k * CHARPIXELWIDTH) + j][i] = __ReverseByte(font8x8_basic[ch][j]);
            }
        }
    }
}

/*!
 * @brief Inverts the byte passed to it
 * @param inByte the char to convert
 */
char __ReverseByte(char inByte)
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
 * @brief Sets the display buffer to contain a single char in the given position
 * @param DB_a The display buffer we'd like to print to
 * @param x The pixel column we wish to print to (Actual number, 0->LCDPIXELMAXX)
 * @param y The row we wish to print to (in pixel location 0->LCDPIXELMAXY
 * @param ch The character we wish to print
 * @param invert Whether to invert the text colour (true for black background/white text)
 */
void __ScreenPrintChar(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]
                       , uint8_t x
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
        if(invert)
        {
            DB_a[y + i][x] = __ReverseByte(~font8x8_basic[chActual][i]);
        }
        else
        {
            DB_a[y + i][x] = __ReverseByte(font8x8_basic[chActual][i]);
        }
    }
}
/*!
 * @brief Writes pixels to where they are wanted on the screen to the displayBuffer
 * @param DB_a The display buffer we'd like to print to
 * @param x The column to start printing, in pixels (multiples of 8)
 * @param y The row to start printing, in pixels (multiples of 8)
 * @param str_p The string we wish to print
 * @param invert true to invert text (black background)
 */
void __ScreenSetText(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]
                     , uint8_t x
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
        __ScreenPrintChar(DB_a
                          ,((x / CHARPIXELWIDTH) + j)
                          , y
                          , (*str_p++)
                          , invert);

        j += 1; /* move to next pixel */
    }
}
/*!
 * @brief Writes lines from the top left, down the screen
 * @param DB_a The display buffer we'd like to print to
 * @param str_p The string we wish to print
 * @param invert true to set background black/white text
 */
void __ScreenPrint(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX]
                   , const char* str_p
                   , bool invert)
{
    uint8_t row = 0;
    uint8_t column = 0;

    while ((*str_p) != '\0')
    {
        char ch = *str_p;
        __ScreenPrintChar(DB_a
                          , column
                          , row
                          , ch
                          , invert);
        column += 1;
        str_p++;

        /* If new line encountered or screen edge found, new line*/
        if (((*str_p) == '\n') || (column >= SCREENMAXX))
        {
            column = 0;
            row += CHARPIXELWIDTH;
            str_p++;
        }
    }
}
/*!
 * @brief Prints a pixel to the provided display buffer
 * @param DB_a The display buffer we'd like to print to
 * @param x The x co-ordinate to print the pixel
 * @param y The y co-ordinate to print the pixel
 * @param invert Whether to invert the square or not
 * 
 * Example funtion below relies on an input of 96x96
 * static void Sharp96x96_PixelDraw(void *pvDisplayData, 
//                                 int16_t lX, 
//                                 int16_t lY,
//                                 uint16_t ulValue)
// {
//     if( ClrBlack == ulValue){
//             DisplayBuffer[lY][lX>>3] &= ~(0x80 >> (lX & 0x7));
//     }else{
//             DisplayBuffer[lY][lX>>3] |= (0x80 >> (lX & 0x7));
//     }
// }
 */
void __ScreenPrintPixel(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX],
                        uint8_t x,
                        uint8_t y,
                        bool invert)
{
    if(invert == true)
    {
        DB_a[y][x] |= 0x01;
    }
    else
    {
        DB_a[y][x] &= ~0x01;
    }
}
// 

/*!
 * @brief shifts the displaybuffer backwards (left) ish
 */
void __ScreenShiftBuffer(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX])
{
    uint8_t x = 0;
    uint8_t y = 0;

    for(; y < LCDPIXELMAXY-(uint8_t)1; ++y)
    {
        /* Start from the left. Shift things left. No pixel left behind */
        for(; x < SCREENMAXX-(uint8_t)1; ++x)
        {
            /* The following is done this way as shifting a number with a '1' in the MSB is undefined */
            /* If the MSB is ON */
            if((DB_a[y][x] & (uint8_t)(0x80)))
            {
                /* Turn it off */
                DB_a[y][x+(uint8_t)1] &= (uint8_t)0x7F;
                /* If within the bounds of the screen */
                if((y+(uint8_t)1 < LCDPIXELMAXY) && (x+(uint8_t)1 < SCREENMAXX))
                {
                    /* "shift" the pixel to the next column */
                    DB_a[y][x+(uint8_t)1] |= (uint8_t)0x01;
                }
            }
            (DB_a[y][x]) = (DB_a[y][x]) << (uint8_t)1;
        }
    }
}
/*!
 * @brief Prints to the display itself
 *
 * The counting up loops are, unfortunately, required in this implementation
 * otherwise nothing appears to work.
 *
 * @param DB_a The array/double pointer to where the display buffer is stored
 *
 * @todo Figure out how to change loops to counting down to improve efficiency
 */
void __ScreenFlushDisplayBuffer(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX])
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
            LCDWriteCommandOrData(DB_a[line][column]);
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

//Work in progress below this point. Please do not touch.

const char Tank[8][4] =
{
        {0x49, 0xFF, 0x82, 0x00},
        {0x49, 0x1C, 0x82, 0xFF},
        {0x49, 0x1C, 0xFE, 0x38},
        {0x7F, 0xFC, 0xFE, 0x38},
        {0x7F, 0x1C, 0xFE, 0x3F},
        {0x7F, 0x1C, 0x92, 0x38},
        {0x41, 0xFF, 0x92, 0x38},
        {0x41, 0x00, 0x92, 0xFF}
};

/*!
 * @brief Creates a splash screen
 * @param
 */
void __ScreenSplashScreen(uint8_t DB_a[LCDPIXELMAXY][SCREENMAXX])
{
    int i;
    int j;

    __ScreenDisplayBufferInit(0xFF, DB_a);

    for (i=0; i<8; i++)
    {
        for(j=0; j<10; j++)
        {
            DB_a[i+72][j] = __ReverseByte(~SplashTitle[j][i]);
        }
    }

//    for (i=0; i<8; i++)
//    {
//        for(j=0; j<6; j++)
//        {
//            DisplayBuffer[i+80][j] = ~font8x8_basic[j][i+10];
//        }
//    }
    int k = 0;

    for (i=0; i<8; i++)
    {
        DB_a[i+10][3] = ~Tank[i][0];
        DB_a[i+10][5] = ~Tank[i][1];
        DB_a[i+10][7] = ~Tank[i][2];
        DB_a[i+10][9] = ~Tank[i][3];
    }

    for (i=0; i<8; i++)
    {
        DB_a[i+k+10][3] = ~Tank[i][2];
        k = (k+1) % 80;
    }
}
