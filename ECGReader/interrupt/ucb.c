#include <msp430fr5969.h>

#include <helpers/boollint.h>
#include <I_lcd.h>
#include <screenHandlerUtility.h>
/* line and column names are now redundant but left in just for piece of mind */
uint32_t column = 0;
uint32_t line = 0;
/*! @brief Write lines (0x80, image update mode ) and VCOM bit (0x40, video communication) */
static const uint8_t command = 0xC0;

extern char __ReverseByte(char inByte);
extern uint8_t DisplayBuffer[LCDPIXELMAXY][SCREENMAXX];

#pragma vector=USCI_B0_VECTOR
__interrupt void UCBSCREEN(void)
{
    switch(UCB0IV) /* Check pin interrupted against */
    {
        default:
            break;
    }
    
    // LCDSetCSHigh();
    // LCDWriteCommandOrData(command);

    // for(line = 0; line < LCDPIXELMAXX; ++line)
    // {
    //     LCDWriteCommandOrData(__ReverseByte(line + 1));

    //     for(column = 0; column < SCREENMAXX; ++column)
    //     {
    //         LCDWriteCommandOrData(DB_a[line][column]);
    //     }
    //     /* EOL byte */
    //     LCDWriteCommandOrData(0x00);
    // }

    
}