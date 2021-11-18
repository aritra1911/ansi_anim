#include <ansi/cursor.h>
#include <graphics/box.h>
#include <graphics/shapes.h>

void draw(const box_t *box)
{
    switch ( box->type ) {
    case RECTANGLE:
        move_cursor(box->origin);
        draw_rectangle(box->width, box->height);
        break;
    }
}
