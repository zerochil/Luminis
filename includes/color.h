#ifndef COLOR_H
# define COLOR_H

#include <libmath.h>

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
} t_color;


void color_clamp(t_color *color);
void color_mul_scalar(t_color *color, double scalar);
void color_add(t_color *color1, t_color *color2);
void color_mul(t_color *color1, t_color *color2);

#endif
