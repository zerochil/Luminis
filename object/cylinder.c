#include "_object.h"

t_uv get_cylinder_uv(t_hit *hit)
{
	t_vec3 p;
	t_vec3 p_local = vec3_sub(hit->point, hit->object->origin);
	t_vec3 cx;
	t_vec3 cy;
	t_vec3 cz = hit->object->orientation;
	create_orthonormal_basis(cz, &cx, &cy);

	p.x = vec3_dot(p_local, cx);
	p.y = vec3_dot(p_local, cy);
	p.z = vec3_dot(p_local, cz);

	double v = p.z / hit->object->height;
	double u = (atan2(p.y, p.x) + M_PI) / (2 * M_PI);
	return (t_uv){u, v};
}

static bool	is_point_within_cylinder_height(t_object *object, t_ray *ray, double t)
{
	t_vec3 hit_point;
    double height;
	double h;

	h = object->height / 2;
	hit_point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, t));
	height = vec3_dot(vec3_sub(hit_point, object->origin), object->orientation);
	if (height < -h || height > h)
        return (false);
	return (true);
}

static t_quadratic_terms cylinder_quadratic_terms(t_object *obj, t_ray *ray)
{
	t_quadratic_terms	qterms;
	t_vec3 V;
	t_vec3 CO;
	t_vec3 D_perp;
	t_vec3 CO_perp;
	
	V = obj->orientation;
    CO = vec3_sub(ray->origin, obj->origin);
	D_perp = vec3_sub(ray->direction, vec3_mul_scalar(V, vec3_dot(ray->direction, V)));
	CO_perp = vec3_sub(CO, vec3_mul_scalar(V, vec3_dot(CO, V)));
    qterms.a = vec3_dot(D_perp, D_perp);
    qterms.b = 2 * vec3_dot(CO_perp, D_perp);
	qterms.c = vec3_dot(CO_perp, CO_perp) - (obj->radius * obj->radius);
	return (qterms);
}
static double cylinder_solution(t_quadratic_terms qterms, t_object *obj, t_ray *ray)
{
	if (qterms.t1 < qterms.t2
	&& is_point_within_cylinder_height(obj, ray, qterms.t1))
		return (qterms.t1);
	if (is_point_within_cylinder_height(obj, ray, qterms.t2))
		return (qterms.t2);
	else
		return (-1);
}

bool intersect_cylinder(t_object *obj, t_ray *ray, t_hit *hit)
{
    t_quadratic_terms	qterms;
	double				height_proj;
	
	qterms = cylinder_quadratic_terms(obj, ray);
    if (quadratic_delta(&qterms) < 0)
		return (false);
	if (quadratic_roots(&qterms) < 0)
		return (false);
	hit->distance = cylinder_solution(qterms, obj, ray);
	if (hit->distance < 0)
		return (false);
	hit->point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, hit->distance));
	height_proj = vec3_dot(
		vec3_sub(hit->point, obj->origin), obj->orientation);
    hit->normal = vec3_normalize(
		vec3_sub(hit->point, 
			vec3_add(obj->origin, 
				vec3_mul_scalar(obj->orientation, height_proj))));
	//hit->normal = vec3_negate_conditionally(vec3_dot(hit->normal, ray->direction) > 0, hit->normal);
	hit->object = obj;
    return true;
}
