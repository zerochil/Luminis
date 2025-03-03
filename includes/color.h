#ifndef COLOR_H
# define COLOR_H

#include <libmath.h>

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
} t_color;


void color_clamp(t_color *color);
void color_mul_scalar(t_color *color, float scalar);
void color_add(t_color *color1, t_color *color2);
void color_mul(t_color *color1, t_color *color2);

#endif
