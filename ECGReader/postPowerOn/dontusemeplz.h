/*!
 * @brief Header file with handlers for hardware, also has an event queue (probably not needed)
 * @author Jesse Batt
 * @date 10/12/2018
 * @todo TIDY EVERYTHING
 */

#ifndef HEADER_H_
#define HEADER_H_

#define WORD unsigned short


int heartbeat = 1;
int counter_button_handler = 0;
#define INTERVAL_BUTTON_HANDLER  10

#define FALSE 0
#define TRUE -1

#define EVENT_NULL          0
#define EVENT_BUTTON_PRESS  1
#define EVENT_FIRE          2
#define EVENT_LEFT          3
#define EVENT_FORWARD       4
#define EVENT_RIGHT         5

/********************************************************************/
/***  Event Queue                                                 ***/
/********************************************************************/

struct Event
{
    char event;
    char param1;
    char param2;
    char param3;
};

#define SIZE_OF_EVENT_Q   6

struct EventQueue
{
    int size;
    int head;
    int tail;
    struct Event queue[SIZE_OF_EVENT_Q];
};

void init_q(struct EventQueue *q)
{
    q->head = 0;
    q->tail = 0;
    q->size = 0;
}

int read_q(struct EventQueue *q, struct Event *e)
{
    int rc;
    int h;
    int s;

    rc = FALSE;

    s = q->size;

    if (s > 0)
    {
        h = q->head;
        e->event  = q->queue[h].event;
        e->param1 = q->queue[h].param1;
        e->param2 = q->queue[h].param2;
        e->param3 = q->queue[h].param3;
        h = (h + 1) % SIZE_OF_EVENT_Q;
        s--;
        q->head = h;
        q->size = s;
        rc = TRUE;
    }

    return rc;
}

int write_q(struct EventQueue *q, struct Event e)
{
    int rc;
    int t;
    int s;

    rc = FALSE;

    s = q->size;

    if (s < SIZE_OF_EVENT_Q)
    {
        t = q->tail;
        q->queue[t].event  = e.event;
        q->queue[t].param1 = e.param1;
        q->queue[t].param2 = e.param2;
        q->queue[t].param3 = e.param3;
        t = (t + 1) % SIZE_OF_EVENT_Q;
        s++;
        q->tail = t;
        q->size = s;
        rc = TRUE;
    }

    return rc;
}



/********************************************************************/
/***  End of Event Queue                                          ***/
/********************************************************************/

struct EventQueue led_q;

/********************************************************************/
/***  Button Handler                                              ***/
/********************************************************************/

void enter_button_state(int new_state);

#define BUTTON_NULL     0
#define BUTTON_RELEASED 1
#define BUTTON_PRESSED  2
#define BUTTON_HELD     3

#define MINIMUM_PRESS_TIME        70
#define BUTTON_HELD_TIME         200

int button_state;
int press_time;
struct Event e;


void init_button_handler()
{
    button_state = BUTTON_RELEASED;
    press_time = 0;
}



/*** BUTTON_RELEASED *********************/

void button_release_enter()
{

}

void button_release_timer()
{
    if ((P1IN & 0x02) == 0)
    {
        // Pressed

        enter_button_state(BUTTON_PRESSED);
    }
}



/*** BUTTON_PRESSED  *********************/

void button_pressed_enter()
{
    press_time = 0;
}

void button_pressed_timer()
{
    press_time++;
    if ((P1IN & 0x02) != 0)
    {
        // Released

        if (press_time >= (MINIMUM_PRESS_TIME/INTERVAL_BUTTON_HANDLER))
        {
            e.event = EVENT_BUTTON_PRESS;
        }
        enter_button_state(BUTTON_RELEASED);
    }
    else
    {
        // Still pressed

        if (press_time >= (BUTTON_HELD_TIME/INTERVAL_BUTTON_HANDLER))
        {
            enter_button_state(BUTTON_HELD);
        }
    }
}



/*** BUTTON_HELD     *********************/

void button_held_enter()
{
    press_time = 0;
    e.event = EVENT_BUTTON_PRESS;
}

void button_held_timer()
{
    press_time++;
    if ((P1IN & 0x02) != 0)
    {
        // Released

        enter_button_state(BUTTON_RELEASED);
    }
    else
    {
        // Still pressed

        if (press_time >= (BUTTON_HELD_TIME/INTERVAL_BUTTON_HANDLER))
        {
            enter_button_state(BUTTON_HELD);
        }
    }
}


/***  Button entry code   *******************************************/

void enter_button_state(int new_state)
{
    switch (new_state)
    {
    case BUTTON_NULL:
        break;

    case BUTTON_RELEASED:
        button_release_enter();
        break;

    case BUTTON_PRESSED:
        button_pressed_enter();
        break;

    case BUTTON_HELD:
        button_held_enter();
        break;

    default:
        break;
    }

    button_state = new_state;
}



/***  Button timer code   *******************************************/

void button_timer()
{
    switch (button_state)
    {
    case BUTTON_NULL:
        break;

    case BUTTON_RELEASED:
        button_release_timer();
        break;

    case BUTTON_PRESSED:
        button_pressed_timer();
        break;

    case BUTTON_HELD:
        button_held_timer();
        break;

    default:
        break;
    }
}

/********************************************************************/
/***  End of Button Handler                                       ***/
/********************************************************************/






/********************************************************************/
/***  LED Handler                                                 ***/
/********************************************************************/


#define LED_OFF  0
#define LED_ON   1
#define LED_PERIOD 50

int led_state  = LED_OFF;
int led_period = 0;
struct Event e;

void led_handler()
{
    led_period++;
    if (led_period >= LED_PERIOD)
    {
        led_period = 0;
        switch (led_state)
        {
        case LED_OFF:
            if (read_q(&led_q, &e))
            {
                if (e.event == EVENT_BUTTON_PRESS)
                {
                    P4OUT |= 0x40;          // Set P4.6 on using OR
                    led_state = LED_ON;
                }
            }
            break;

        case LED_ON:
            P4OUT &= (0xFF-0x40);   // Set P4.6 off using AND
            led_state = LED_OFF;
            break;

        default:
            break;
        }
    }
}

/********************************************************************/
/***  End of LED Handler                                          ***/
/********************************************************************/



/********************************************************************/
/***  Slider Handler                                              ***/
/********************************************************************/

#define SLIDER_NULL             0
#define SLIDER_READ_UPPER_LEFT  1
#define SLIDER_READ_UPPER_RIGHT 2
#define SLIDER_READ_LOWER_LEFT  3
#define SLIDER_READ_LOWER_RIGHT 4








/********************************************************************/
/***  End of Slider Handler                                       ***/
/********************************************************************/







/********************************************************************/
/***  LCD Handler                                                 ***/
/********************************************************************/


const int Font[8][16] =
{
        //  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {0x28, 0x08, 0x18, 0x3C, 0x10, 0x3C, 0x08, 0x3E, 0x3C, 0x3C, 0x18, 0x38, 0x38, 0x30, 0x3C, 0x3C},
        {0x44, 0x18, 0x24, 0x04, 0x10, 0x20, 0x10, 0x02, 0x24, 0x44, 0x24, 0x24, 0x44, 0x28, 0x20, 0x20},
        {0x44, 0x08, 0x08, 0x08, 0x20, 0x38, 0x20, 0x04, 0x18, 0x44, 0x24, 0x24, 0x40, 0x24, 0x38, 0x3C},
        {0x44, 0x08, 0x10, 0x18, 0x24, 0x04, 0x3C, 0x08, 0x24, 0x3C, 0x3C, 0x38, 0x40, 0x24, 0x20, 0x20},
        {0x44, 0x08, 0x10, 0x04, 0x3E, 0x04, 0x24, 0x10, 0x24, 0x04, 0x24, 0x24, 0x44, 0x24, 0x20, 0x20},
        {0x28, 0x3C, 0x3C, 0x38, 0x04, 0x38, 0x18, 0x10, 0x3C, 0x04, 0x24, 0x38, 0x38, 0x38, 0x3C, 0x20},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};


char DisplayBuffer[96][96/8];

char row_modified[96];
char row_previously_modified[96];


int reverse(int inint)
{
    int outint;

    outint = 0;

    if ((inint & BIT0) > 0) outint |= BIT7;
    if ((inint & BIT1) > 0) outint |= BIT6;
    if ((inint & BIT2) > 0) outint |= BIT5;
    if ((inint & BIT3) > 0) outint |= BIT4;
    if ((inint & BIT4) > 0) outint |= BIT3;
    if ((inint & BIT5) > 0) outint |= BIT2;
    if ((inint & BIT6) > 0) outint |= BIT1;
    if ((inint & BIT7) > 0) outint |= BIT0;

    return outint;
}


void initDisplayWriting()
{
    int i;

    for (i=0; i<96; i++)
    {
        row_modified[i] = 1;
    }
}


void initDisplayBuffer(int setting)
{
    int i;
    int j;

    for (i=0; i<96; i++)
    {
        for(j=0; j<12; j++)
        {
            DisplayBuffer[i][j] = setting;
        }

        row_previously_modified[i] = row_modified[i];
        row_modified[i] = 0;
    }
}


void outputDisplayBuffer()
{
    int line;
    int column;
    int command = 0x80;             // Write lines

    command = command ^ 0x40;       // VCOM bit

    P2OUT |= 0x10;                  // LCD CS high

    while (!(UCB0IFG & UCTXIFG));
    UCB0TXBUF = command;

    for (line=0; line<96; line++)
    {
        if ((row_modified[line] | row_previously_modified[line]) != 0)
        {
            while (!(UCB0IFG & UCTXIFG));
            UCB0TXBUF = reverse(line+1);

            for (column=0; column<12; column++)
            {
                while (!(UCB0IFG & UCTXIFG));
                UCB0TXBUF = DisplayBuffer[line][column];
            }

            while (!(UCB0IFG & UCTXIFG));
            UCB0TXBUF = 0x00;            // End of line signal
        }
    }

    while (!(UCB0IFG & UCTXIFG));
    UCB0TXBUF = 0x00;               // End of block signal

    while ((UCB0STATW & UCBBUSY));

    __delay_cycles(8);              //Ensure a 2us min delay to meet the LCD's thSCS

    P2OUT &= ~0x10;                 // LCD CS low
}


void outputHex(int row, int column, WORD number)
{
    int i;

    for (i=0; i<8; i++)
    {
        DisplayBuffer[i+row][column  ] ^= Font[i][(number>>12) & 0x0F];
        DisplayBuffer[i+row][column+1] ^= Font[i][(number>>8 ) & 0x0F];
        DisplayBuffer[i+row][column+2] ^= Font[i][(number>>4 ) & 0x0F];
        DisplayBuffer[i+row][column+3] ^= Font[i][(number    ) & 0x0F];
    }
}

int k = 0;

void buildScene()
{
    initDisplayBuffer(0xFF);
/*
    outputHex(30, 1, slider_upper_left );
    outputHex(40, 1, slider_lower_left );
    outputHex(30, 7, slider_upper_right);
    outputHex(40, 7, slider_lower_right);
*/

}



int display_state = 0;
int line;
int column;

void lcd_handler()
{
    switch (display_state)
    {
    case 0: // build scene
        buildScene();
        display_state = 1;
        break;

    case 1: // display scene
        if (UCB0IFG & UCTXIFG)
        {
            if (line == 0)
            {
                P2OUT |= 0x10;                  // Enable LCD CS
                UCB0TXBUF = 0x80;
                column = 0;
                line++;
            }
            else if ((line >= 1) && (line <= 96))
            {
                if ((row_modified[line-1] | row_previously_modified[line-1]) != 0)
                {
                    if (column == 0)
                    {
                        UCB0TXBUF = reverse(line);
                        column++;
                    }
                    else if ((column >= 1) && (column <= 12))
                    {
                        UCB0TXBUF =  DisplayBuffer[line-1][column-1];
                        column++;
                    }
                    else
                    {
                        UCB0TXBUF = 0x00;
                        column = 0;
                        line++;
                    }
                }
                else
                {
                    column = 0;
                    line++;
                }
            }
            else if (line == 97)
            {
                UCB0TXBUF = 0x00;
                line++;
            }
            else if (line == 98)
            {
                line++;
            }
            else
            {
                if ((UCB0STATW & UCBBUSY) == 0)
                {
                    line = 0;
                    P2OUT &= ~0x10;                 // Disable LCD CS
                    display_state = 0;
                }
            }
        }
        break;

    default:
        display_state = 0;
        break;
    }
}



/********************************************************************/
/***  End of LCD Handler                                          ***/
/********************************************************************/

#endif /* HEADER_H_ */
