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

t_vec3 color_new(double color)
{
	int x;
	int y;
	int z;
	t_vec3 color_vec;

	z = (int)color & 0xFF;
	y = ((int)color >> 8) & 0xFF;
	x = ((int)color >> 16) & 0xFF;

	color_vec.x = x / 255.0;
	color_vec.y = y / 255.0;
	color_vec.z = z / 255.0;


	return (color_vec);
}

t_vec3 evaluate_colored_texture(t_texture *texture, struct s_hit *hit)
{
	t_uv uv;
	double texel;

	uv = hit->object->get_uv(hit);
	texel = texel_value(texture, uv);
	return (color_new(texel));
}
