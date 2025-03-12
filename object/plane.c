#include "_object.h"

t_uv get_plane_uv(t_hit *hit)
{
	/*t_vec3 p;*/
	/*t_vec3 p_local = vec3_sub(hit.point, hit.object->origin);*/
	/*t_vec3 cx;*/
	/*t_vec3 cy;*/
	/*t_vec3 cz = hit.object->orientation;*/
	/*create_orthonormal_basis(cz, &cx, &cy);*/
	/**/
	/*p.x = vec3_dot(p_local, cx);*/
	/*p.y = vec3_dot(p_local, cy);*/
	/*p.z = vec3_dot(p_local, cz);*/
	/**/
	/*return (t_uv){p.x, p.y};*/
	// TODO: Implement UV mapping for planes
	(void)hit;
	return ((t_uv){0, 0});
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
