#include <object.h>

t_vec3 evaluate_solid_texture(t_texture *texture, t_hit *hit)
{
	(void)texture;
	(void)hit;
	return (hit->object->color);
}
