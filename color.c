#include <color.h>

t_color color_mul_scalar(t_color color, float scalar)
{
	t_color result;

	result.r = color.r * scalar;
	result.g = color.g * scalar;
	result.b = color.b * scalar;
	return (result);
}

void color_clamp(t_color *color)
{
	color->r = fmin(fmax(color->r, 0), 1);
	color->g = fmin(fmax(color->g, 0), 1);
	color->b = fmin(fmax(color->b, 0), 1);
}
