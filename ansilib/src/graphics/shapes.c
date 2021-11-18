#include <ansi/cursor.h>
#include <graphics/shapes.h>

#include <io.h>

void draw_rectangle(point_t pos, uint32_t width, uint32_t height)
{
    move_cursor(pos);

    /* Top edge */
    for (uint32_t i = 0; i < width; i++) {
        printmsg("#");
    }

    for (uint32_t i = 0; i < height - 2; i++) {

        /* Get to the next line */
        nudge_cursor(LEFT, width);
        nudge_cursor(DOWN, 1);

        /* Left edges */
        printmsg("#");

        /* Right edges */
        nudge_cursor(RIGHT, width - 2);
        printmsg("#");
    }

    /* Get to the next line */
    nudge_cursor(LEFT, width);
    nudge_cursor(DOWN, 1);

    /* Bottom edge */
    for (uint32_t i = 0; i < width; i++) {
        printmsg("#");
    }
}
