#ifndef __COLORS_H_
# define __COLORS_H_

# include <stdint.h>

typedef enum : uint32_t {
    BLACK,      /* 0 */
    RED,        /* 1 */
    GREEN,      /* 2 */
    YELLOW,     /* 3 */
    BLUE,       /* 4 */
    MAGENTA,    /* 5 */
    CYAN,       /* 6 */
    WHITE,      /* 7 */
    DEFAULT,    /* 8 */
} color_t;

typedef enum : uint32_t {
    BACKGROUND      = ( 1 << 0 ),
    BRIGHT          = ( 1 << 1 ),
    FAINT           = ( 1 << 2 ),
    BOLD            = ( 1 << 3 ),
    ITALIC          = ( 1 << 4 ),
    UNDERLINE       = ( 1 << 5 ),
    STRIKETHROUGH   = ( 1 << 6 ),
    BLINKING        = ( 1 << 7 ),
    INVERSE         = ( 1 << 8 ),
    INVISIBLE       = ( 1 << 9 ),
} mode_t;

void set_color();

#endif  /* __COLORS_H_ */
