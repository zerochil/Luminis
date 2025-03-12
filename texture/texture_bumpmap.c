#include <object.h>

static double bump_value(t_texture *texture, t_uv uv)
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

static void calculate_perturbed_normal(struct s_hit *hit, double bump)
{
	t_vec3 tangent;
	t_vec3 bitangent;
	t_vec3 perturbed_normal;
	double coeff;

	coeff = .9;
	create_orthonormal_basis(hit->normal, &tangent, &bitangent);
	perturbed_normal = vec3_add(hit->normal, vec3_mul_scalar(bitangent, (bump) * coeff));
	//t_vec3 perturbed_normal = vec3_add(hit.normal, vec3_mul_scalar(vec3_add(tangent, bitangent), tex_val * coeff));
	hit->normal = vec3_add(hit->normal, perturbed_normal);
	hit->normal = vec3_normalize(hit->normal);
}

t_vec3 evaluate_bump_map_texture(t_texture *texture, struct s_hit *hit)
{
	t_uv uv;
	double bump;

	uv = hit->object->get_uv(hit);
	bump = bump_value(texture, uv);
	calculate_perturbed_normal(hit, bump);
	return(hit->object->color);
}
