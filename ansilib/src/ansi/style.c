#include <stdio.h>
#include <string.h>

#include <io.h>
#include <ansi/common.h>
#include <ansi/colors.h>
#include <ansi/style.h>

static char *get_text_mode_str(text_mode_t m, char *mode_str)
{
    int  barf = 1;
    char temp[4];

    memset(mode_str, 0, (size_t) 32);

    while ( m ) {

        if ( m & 1 ) {
            sprintf(temp, "%i;", barf);
            strcat(mode_str, temp);
        }

        /* No six? Skip six! */
        barf = (barf == 5) ? 7 : barf + 1;
        m >>= 1;
    }

    return mode_str;
}

void set_style(const style_t *s)
{
    char text_mode_str[32],
         buf[32],
         temp[32];

    sprintf(buf, CSI);

    get_text_mode_str(s->text_mode_mask, text_mode_str);
    strcat(buf, *text_mode_str ? text_mode_str : "0;");

    if ( s->fg ) {
        sprintf(temp, "%i;", s->fg);
        strcat(buf, temp);
    }

    if ( s->bg ) {
        sprintf(temp, "%i;", s->bg);
        strcat(buf, temp);
    }

    if ( buf[strlen(buf) - 1] == ';' )
        buf[strlen(buf) - 1] = 'm';
    else
        strcat(buf, "m");

    printws(NULL, buf);
}

void reset_all(void)
{
    printws(NULL, CSI"0m");
}
