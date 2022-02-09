#ifndef __ANSI_STYLE_H_
# define __ANSI_STYLE_H_

# include <ansi/colors.h>

typedef struct {
    color_t internal_fg, internal_bg;
    color_t border_fg, border_bg;
    text_mode_t text_mode_mask;
} style_t;

void set_style(const style_t *);
void reset_all(void);

#endif  /* __ANSI_STYLE_H_ */
