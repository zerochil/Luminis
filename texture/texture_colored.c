#include <object.h>
static double texel_value(t_texture *texture, t_uv uv)
{
	int x = (int)(uv.u * texture->bump_map.width) % texture->bump_map.width;
	int y = (int)((uv.v) * texture->bump_map.height) % texture->bump_map.height;
	if (x < 0)
		x = 0;
	if (x >= texture->bump_map.width)
		x = texture->bump_map.width - 1;
	if (y < 0)
		y = 0;
	if (y >= texture->bump_map.height)
		y = texture->bump_map.height - 1;
	return (texture->bump_map.ptr[y * texture->bump_map.width + x]);
}

t_vec3 evaluate_colored_texture(t_texture *texture, struct s_hit *hit)
{
	t_uv uv;
	double texel;

	uv = hit->object->get_uv(hit);
	return (texel_value(texture, uv));
}
