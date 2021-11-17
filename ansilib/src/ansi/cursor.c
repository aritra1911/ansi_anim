#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#include <ansi/common.h>
#include <ansi/cursor.h>

point_t get_cursor_pos(void)
{
    char buf[16];
    point_t ret = { 0 };

    /* ESC[6n   request cursor position (reports as ESC[#;#R) */

    write(STDOUT_FILENO, CSI"6n", 4);
    if ( read(STDIN_FILENO, buf, 16) ) {

        uint32_t line, column;
        sscanf(buf, CSI"%"PRIu32";%"PRIu32"R", &line, &column);

        ret.x = column;
        ret.y = line;
    }

    return ret;
}

void move_cursor(point_t pos)
{
    char buf[16];

    /*
     * ESC[{line};{column}H
     * or
     * ESC[{line};{column}f
     */

    sprintf(buf, CSI"%i;%iH", pos.y, pos.x);
    write(STDOUT_FILENO, (void *) buf, strlen(buf));
}

void nudge_cursor(dir_t direction, uint32_t step)
{
    /* TODO: `direction` is a bitmask */
    char buf[16], end_ch;

    /*
     * ESC[#A   moves cursor up # lines
     * ESC[#B   moves cursor down # lines
     * ESC[#C   moves cursor right # columns
     * ESC[#D   moves cursor left # columns
     */

    switch ( direction ) {
        case UP:    end_ch = 'A'; break;
        case DOWN:  end_ch = 'B'; break;
        case RIGHT: end_ch = 'C'; break;
        case LEFT:  end_ch = 'D';
    }

    sprintf(buf, CSI"%i%c", step, end_ch);
    write(STDOUT_FILENO, (void *) buf, strlen(buf));
}
