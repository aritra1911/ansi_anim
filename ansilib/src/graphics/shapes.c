#include <stddef.h>

#include <io.h>
#include <ansi/cursor.h>
#include <ansi/style.h>
#include <graphics/shapes.h>


void draw_rectangle(style_t style,uint32_t width, uint32_t height, char ch)
{
    /* Top edge */
    for (uint32_t i = 0; i < width; i++) {
        /* TODO: This character should be an argument such as
         *       `border_char`. Also, let's not forget about
         *       `border_width` */
        printws(&style, "%c", ch);
    }

    for (uint32_t i = 0; i < height - 2; i++) {

        /* TODO: Add fill character argument.
         *       If fill character is not '\0', we should fill the
         *       rectangle with that character. */

        /* Get to the next line */
        nudge_cursor(LEFT, width);
        nudge_cursor(DOWN, 1);

        /* Left edges */
        printws(&style, "%c", ch);

        /* Right edges */
        nudge_cursor(RIGHT, width - 2);
        printws(&style, "%c", ch);
    }

    /* Get to the next line */
    nudge_cursor(LEFT, width);
    nudge_cursor(DOWN, 1);

    /* Bottom edge */
    for (uint32_t i = 0; i < width; i++) {
        printws(&style, "%c", ch);
    }
}

void draw_triangle(style_t style, uint32_t height, char ch)
{
  /*  Draws a triangle, on the basis of height   */

    for (uint32_t i = 0; i < height - 1; i++) {

        /* TODO: Add fill character argument.
         *       If fill character is not '\0', we should fill the
         *       rectangle with that character. */

        /* right arm*/
        printws(&style , "%c", ch);
        nudge_cursor(DOWN, 1);

    }

    /* Bottom side  */
    nudge_cursor(LEFT, 2*(height-1) );
    for(uint32_t i = 2*(height - 1) +1 ; i > 0; i--)
      printws(&style, "%c", ch);
    nudge_cursor(LEFT, 2*(height-1) + 1);

    for (uint32_t i = 0; i < height - 1; i++) {

        /* TODO: Add fill character argument.
         *       If fill character is not '\0', we should fill the
         *       rectangle with that character. */

        /* right arm*/
        printws(&style, "%c", ch);
        nudge_cursor(UP, 1);

    }
}
