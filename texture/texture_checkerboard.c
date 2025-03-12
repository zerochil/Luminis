#include <object.h>

t_vec3 evaluate_checkerboard_texture(t_texture *texture, struct s_hit *hit)
{
	t_uv uv;
	t_vec3 color;

	(void)texture;
	uv = hit->object->get_uv(hit);
	double i = floor(uv.u * 100);
	double j = floor(uv.v * 100);

	if ((int)floor(i + j) % 2 == 0)
		color = (t_vec3){255, 255, 255};
	else
		color = (t_vec3){0, 0, 0};
	return color;
}
