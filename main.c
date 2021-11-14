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
