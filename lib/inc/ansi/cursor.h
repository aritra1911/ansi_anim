#ifndef __ANSI_CURSOR_H_
# define __ANSI_CURSOR_H_

# include <graphics/common.h>

typedef enum { LEFT, DOWN, UP, RIGHT } dir_t;

void move_cursor(point_t);
void nudge_cursor(dir_t, uint32_t step);

#endif  /* __ANSI_CURSOR_H_ */
