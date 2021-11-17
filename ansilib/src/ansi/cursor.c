#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <ansi/common.h>
#include <ansi/cursor.h>

void move_cursor(point_t pos)
{
    char buf[16];

    /*
     * ESC[{line};{column}H
     * or
     * ESC[{line};{column}f
     */

    sprintf(buf, CSI"%i;%iH", /* line */ pos.y, /* column */ pos.x);
    write(STDOUT_FILENO, (void *) buf, strlen(buf));
}

void nudge_cursor(dir_t direction, uint32_t step)
{
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
    case LEFT:  end_ch = 'D'; break;
    }

    sprintf(buf, CSI"%i%c", step, end_ch);
    write(STDOUT_FILENO, (void *) buf, strlen(buf));
}
