#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;    /* Keeps the original attributes */

static inline void enable_raw_mode(void);
static inline void disable_raw_mode(void);

static inline void enable_raw_mode(void)
{
    struct termios raw;

    atexit(disable_raw_mode);   /* defer call to disable_raw_mode() */

    /* Fetch the current attributes and save it */
    tcgetattr(STDIN_FILENO, &orig_termios);
    raw = orig_termios;

    raw.c_lflag &= ~(ECHO); /* turn off echoing */

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

    /* keep reading until EOF or 'q' */
    while ( read(STDIN_FILENO, &c, 1) && c != 'q' );

    return EXIT_SUCCESS;
}
