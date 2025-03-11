#include "_object.h"

static double cone_solution(t_quadratic_terms qterms)
{
	if (qterms.t1 < 0)
		return (qterms.t2);
	else if (qterms.t2 < 0)
		return (qterms.t1);
	else
		return (fmin(qterms.t1, qterms.t2));
}
static t_quadratic_terms	cone_quadratic_terms(t_object *obj, t_ray *ray, double k2)
{
	t_quadratic_terms qterms;
	t_vec3 o;
	double dv;
	double ov;

	dv = vec3_dot(ray->direction, obj->orientation);
	o = vec3_sub(ray->origin, obj->origin);
	ov = vec3_dot(o, obj->orientation);
    qterms.a = vec3_dot(ray->direction, ray->direction) - (1 + k2) * (dv * dv);
    qterms.b = 2 * (vec3_dot(o, ray->direction) - (1 + k2) * (ov * dv));
    qterms.c = vec3_dot(o, o) - (1 + k2) * (ov * ov);
	return (qterms);
}

bool		intersect_cone(t_object *obj, t_ray *ray, t_hit *hit)
{
	t_quadratic_terms qterms;
	t_vec3 local_point;
	t_vec3 axis_comp;
	double k2;

	k2 = pow2(tan(obj->angle * (M_PI / 180)));
	qterms = cone_quadratic_terms(obj, ray, k2);
	if (quadratic_delta(&qterms) < 0)
		return (false);
	if (quadratic_roots(&qterms) < 0)
		return (false);
	hit->distance = cone_solution(qterms);
	hit->point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, hit->distance));
	local_point = vec3_sub(hit->point, obj->origin);
	axis_comp = vec3_mul_scalar(obj->orientation, 
		(1 + k2) * vec3_dot(obj->orientation, local_point));
	hit->normal = vec3_normalize(vec3_sub(local_point, axis_comp));	
	hit->normal = vec3_negate_conditionally(vec3_dot(hit->normal, ray->direction) > 0, hit->normal);
	hit->object = obj;
	return (true);
}