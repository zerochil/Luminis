#include "_object.h"

t_uv get_plane_uv(t_hit *hit)
{
	t_uv uv;
	t_vec3 p_local;
	t_vec3 tangent;
	t_vec3 bitangent;
	t_vec3 normal;

	normal = hit->object->orientation;
	p_local = vec3_sub(hit->point, hit->object->origin);
	create_orthonormal_basis(normal, &tangent, &bitangent);

	uv.u = fmod(vec3_dot(p_local, tangent) / 100, 1);
	uv.v = fmod(vec3_dot(p_local, bitangent) / 100, 1);

	return uv;
}

bool		intersect_plane(t_object *object, t_ray *ray, t_hit *hit)
{
	double t;
	double denominator;
	t_vec3 normal;
	t_vec3 position;

	normal = object->orientation;
	denominator = vec3_dot(normal, ray->direction);
	if (float_eq(denominator, 0))
		return (false);
	position = vec3_sub(object->origin, ray->origin);
	t = vec3_dot(position, normal) / denominator;
	if (t <= 0)
		return (false);
	hit->distance = t;
	hit->normal = vec3_negate_conditionally((denominator > 0), normal);
	hit->object = object;
	hit->point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, t));
	return (true);
}
