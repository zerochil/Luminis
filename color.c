#include <color.h>

void color_mul_scalar(t_color *color, double scalar)
{
	color->r *= scalar;
	color->g *= scalar;
	color->b *= scalar;
}

void color_add(t_color *color1, t_color *color2)
{
	color1->r += color2->r;
	color1->g += color2->g;
	color1->b += color2->b;
}

void color_clamp(t_color *color)
{
	color->r = fmin(fmax(color->r, 0.0), 1.0);
	color->g = fmin(fmax(color->g, 0.0), 1.0);
	color->b = fmin(fmax(color->b, 0.0), 1.0);
}

void color_mul(t_color *color1, t_color *color2)
{
	color1->r *= color2->r;
	color1->g *= color2->g;
	color1->b *= color2->b;
}
