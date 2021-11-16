#include <unistd.h>

#include <ansi/cursor.h>
#include <graphics/shapes.h>

void draw_rectangle(point_t pos, uint32_t width, uint32_t height)
{
    move_cursor(pos);

    /* Top Edge */
    for (uint32_t i = 0; i < width; i++) {
        write(STDOUT_FILENO, (void *) "#", 1);
    }

    for (uint32_t i = 0; i < height - 2; i++) {

        /* Get to the next line */
        nudge_cursor(LEFT, width);
        nudge_cursor(DOWN, 1);

        /* print left and right edges */
        write(STDOUT_FILENO, (void *) "#", 1);
        for (uint32_t j = 0; j < width - 2; j++) {
            write(STDOUT_FILENO, (void *) " ", 1);
        }
        write(STDOUT_FILENO, (void *) "#", 1);
    }

    /* Get to the next line */
    nudge_cursor(LEFT, width);
    nudge_cursor(DOWN, 1);

    /* Bottom Edge */
    for (uint32_t i = 0; i < width; i++) {
        write(STDOUT_FILENO, (void *) "#", 1);
    }
}
