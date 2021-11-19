#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include <io.h>
#include <ansi/cursor.h>
#include <ansi/screen.h>
#include <graphics/common.h>
#include <graphics/box.h>

struct termios orig_termios;    /* Keeps the original attributes */

static inline void enable_raw_mode(void);
static inline void disable_raw_mode(void);

static inline void enable_raw_mode(void)
{
    struct termios raw;

    atexit(disable_raw_mode);   /* defer call to disable_raw_mode() */

    /* Fetch the current attributes and keep a copy */
    tcgetattr(STDIN_FILENO, &orig_termios);
    raw = orig_termios;

    /* turn off a bunch of things:
     *      BRKINT  : send SIGINT on break
     *      ICRNL   : translation of '\r' to '\n'
     *      INPCK   : parity checking
     *      ISTRIP  : strip 8th bit of every input byte
     *      IXON    : software flow control (^S and ^Q)
     *      OPOST   : translation of "\n" to "\r\n"
     *      ECHO    : echoing of characters
     *      ICANON  : canonical mode (not reading byte-by-byte)
     *      IEXTEN  : ^V
     *      ISIG    : signals like SIGINT (on ^C) and SIGSTP (on ^Z)
     */
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    /* Set character size to 8 bits per byte.
     * This isn't always necessary */
    raw.c_cflag |= (CS8);

    /* Set timeout for read() */
    raw.c_cc[VMIN] = 0;     /* read() returns as soon as there's input */
    raw.c_cc[VTIME] = 1;    /* read() times out after 100 milliseconds */

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

static inline void disable_raw_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

int main(void)
{
    char c;

    enable_raw_mode();

    /* print out screen size */
    point_t screen_size = get_screen_size();
    printf("LINES = %i  COLUMNS = %i\r\n", screen_size.y, screen_size.x);

    /* Draw beautiful geometric rectangles of various sizes at various
     * places all over the screen. */
    box_t rects[] = {
        { RECTANGLE, { 20, 12 }, 12, 13 },
        { RECTANGLE, { 52,  7 },  7,  8 },
        { RECTANGLE, { 42, 30 }, 20, 16 },
        { RECTANGLE, { 72, 12 }, 32, 16 },
    };

    point_t orig_cursor_pos = get_cursor_pos();
    for (int i = 0; i < 4; i++) {
        draw(&rects[i]);
    }
    move_cursor(orig_cursor_pos);

    while ( 1 ) {
        /* Read a byte from the standard input */
        while ( read(STDIN_FILENO, &c, 1) < 1 );

        if ( !iscntrl(c) ) {
            if ( c == 'q' ) break;
            else if ( c == 'h' || c == 'j' || c == 'k' || c == 'l' ) {
                orig_cursor_pos = get_cursor_pos();
                erase(&rects[0]);
                switch ( c ) {
                case 'h':
                    nudge(&rects[0], LEFT, 1);
                    break;
                case 'j':
                    nudge(&rects[0], DOWN, 1);
                    break;
                case 'k':
                    nudge(&rects[0], UP, 1);
                    break;
                case 'l':
                    nudge(&rects[0], RIGHT, 1);
                    break;
                }
                draw(&rects[0]);
                move_cursor(orig_cursor_pos);
            }
        }
    }

    return EXIT_SUCCESS;
}
