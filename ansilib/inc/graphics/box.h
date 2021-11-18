#ifndef __GRAPHICS_BOX_H_
# define __GRAPHICS_BOX_H_

# include <graphics/common.h>

typedef enum {
    RECTANGLE,
} shape_t;

typedef struct {
    shape_t type;
    point_t origin;
    uint32_t width, height;
} box_t;

void draw(const box_t *box);

#endif  /* __GRAPHICS_BOX_H_ */
