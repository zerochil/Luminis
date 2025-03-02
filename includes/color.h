#ifndef COLOR_H
# define COLOR_H

#include <libmath.h>

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
} t_color;


t_color color_mul_scalar(t_color color, float scalar);
void color_clamp(t_color *color);

#endif
