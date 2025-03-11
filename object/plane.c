#include "_object.h"

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