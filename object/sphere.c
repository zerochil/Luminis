#include "_object.h"

static double sphere_solution(t_quadratic_terms qterms)
{
	if (qterms.t1 < 0)
		return (qterms.t2);
	else if (qterms.t2 < 0)
		return (qterms.t1);
	else
		return (fmin(qterms.t1, qterms.t2));
}

bool		intersect_sphere(t_object *object, t_ray *ray, t_hit *hit)
{
	t_quadratic_terms qterms;
	t_vec3 pos;
	t_vec3 direction;

	direction = vec3_sub(ray->origin, object->origin);
	qterms.a = 1;
	qterms.b = 2 * vec3_dot(ray->direction, direction);
	qterms.c = vec3_dot(direction, direction) - object->radius * object->radius;
	if (quadratic_delta(&qterms) < 0)
		return (false);
	if (quadratic_roots(&qterms) < 0)
		return (false);
	hit->distance = sphere_solution(qterms);
	pos = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, hit->distance));
	hit->normal = vec3_normalize(vec3_sub(pos, object->origin));
	hit->normal = vec3_negate_conditionally(
		vec3_length(direction) <= object->radius, hit->normal);
	hit->object = object;
	hit->point = pos;
	return (true);
}