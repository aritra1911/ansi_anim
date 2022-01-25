#ifndef __GRAPHICS_SHAPES_H_
# define __GRAPHICS_SHAPES_H_

# include <stdint.h>

# include <graphics/common.h>

void draw_rectangle(style_t style,uint32_t width, uint32_t height, char ch);
void draw_triangle(style_t style, uint32_t height, char ch);

#endif  /* __GRAPHICS_SHAPES_H_ */
