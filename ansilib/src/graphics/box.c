#include <stdint.h>
#include <stdlib.h>

#include <ansi/cursor.h>
#include <graphics/box.h>
#include <graphics/shapes.h>

void draw(const box_t *box)
{
    switch ( box->type ) {
    case RECTANGLE:
        move_cursor(box->origin);
        draw_rectangle(box->style, box->width, box->height, '#');
        break;
    case TRIANGLE:
        move_cursor(box->origin);
        draw_triangle(box->style,  box->height, '*');
        break;
    }
}

void erase(const box_t *box)
{
  style_t null = {0,0,NONE};
    switch ( box->type ) {
    case RECTANGLE:
        move_cursor(box->origin);
        draw_rectangle(null, box->width, box->height, ' ');
        break;
    case TRIANGLE:
        move_cursor(box->origin);
        draw_triangle(null, box->height, ' ');
        break;
    }
}

void nudge(box_t *box, dir_t dir, int32_t steps)
{
    switch ( dir ) {
    case UP:
        box->origin.y -= steps;
        break;

    case DOWN:
        box->origin.y += steps;
        break;

    case LEFT:
        box->origin.x -= steps;
        break;

    case RIGHT:
        box->origin.x += steps;
        break;
    }
}
