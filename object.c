#include "object.h"

bool		intersect_plane(t_object *object, t_ray *ray, t_hit *hit)
{
	double t;
	double denominator;
	t_vec3 normal;
	t_vec3 position;

	normal = object->plane.normal;
	denominator = vec3_dot(normal, ray->direction);
	if (float_eq(denominator, 0))
		return (false);
	position = vec3_sub(object->origin, ray->origin);
	t = vec3_dot(position, normal) / denominator;
	if (t > 0) // should be t >= 0
	{
		hit->distance = t;
		hit->normal = (denominator > 0) ? vec3_negate(normal): normal;
		hit->object = object;
		hit->point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, t));
		return (true);
	}
	return (false);
}

bool	test(t_object *object, t_vec3 hit_point)
{
    double height_proj = vec3_dot(vec3_sub(hit_point, object->origin), object->cylinder.orientation);
	return true;
	if (height_proj < 0 || height_proj > object->cylinder.height)
        return false;
	return true;
}

bool intersect_cylinder(t_object *object, t_ray *ray, t_hit *hit)
{
    t_vec3 V = object->cylinder.orientation;
    t_vec3 CO = vec3_sub(ray->origin, object->origin);

    t_vec3 D_perp = vec3_sub(ray->direction, vec3_mul_scalar(V, vec3_dot(ray->direction, V)));
    t_vec3 CO_perp = vec3_sub(CO, vec3_mul_scalar(V, vec3_dot(CO, V)));

    double A = vec3_dot(D_perp, D_perp);
    double B = 2 * vec3_dot(CO_perp, D_perp);
    double C = vec3_dot(CO_perp, CO_perp) - (object->cylinder.radius * object->cylinder.radius);

    double discriminant = B * B - 4 * A * C;
    if (discriminant < 0)
        return false;

    double t1 = (-B - sqrt(discriminant)) / (2 * A);
    double t2 = (-B + sqrt(discriminant)) / (2 * A);
	if (t1 < 0 && t2 < 0)
		return false;
	t_vec3 hit_point;
	t_vec3 hit_point1 = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, t1));
	t_vec3 hit_point2 = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, t2));
	if (t1 < t2 && test(object, hit_point1))
	{
		hit_point = hit_point1;
		hit->distance = t1;
	}
	else if (test(object, hit_point2))
	{
		hit->distance = t2;
		hit_point = hit_point2;
	}
	else
		return false;
	double height_proj = vec3_dot(vec3_sub(hit_point, object->origin), object->cylinder.orientation);
    hit->point = hit_point;
    hit->normal = vec3_normalize(vec3_sub(hit_point, vec3_add(object->origin, vec3_mul_scalar(V, height_proj))));
	hit->object = object;
    return true;
}


bool		intersect_sphere(t_object *object, t_ray *ray, t_hit *hit)
{
	double b;
	double c;
	double delta;
	double t1;
	double t2;
	t_vec3 position;
	t_vec3 direction;

	direction = vec3_sub(ray->origin, object->origin);
	b = 2 * vec3_dot(ray->direction, direction);
	c = vec3_dot(direction, direction) - object->sphere.radius * object->sphere.radius;
	delta = b * b - 4 * c;
	if (delta < 0)
		return (false);
	t1 = (-b - sqrt(delta)) / 2.0;
	t2 = (-b + sqrt(delta)) / 2.0;
	if (t1 < 0 && t2 < 0)
		return (false);
	if (t1 < 0 && t2 < 0)
		return (false);
	if (t1 < 0)
		hit->distance = t2;
	else if (t2 < 0)
		hit->distance = t1;
	else
		hit->distance = fmin(t1, t2);
	if (hit->distance < 0)
		return (false);
	position = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, hit->distance));
	hit->normal = vec3_normalize(vec3_sub(position, object->origin));
	hit->normal = vec3_length(direction) > object->sphere.radius ? hit->normal: vec3_negate(hit->normal);
	hit->object = object;
	hit->point = position;
	return (true);
}

t_intersect object_intersection(enum e_object type)
{
	if (type == SPHERE)
		return (intersect_sphere);
	if (type == PLANE)
		return (intersect_plane);
	if (type == CYLINDER)
		return (intersect_cylinder);
	return (NULL);
}

t_object	*object_create(enum e_object type)
{
	t_object	*object;

	object = track_malloc(sizeof(t_object));
	object->type = type;
	object->intersect = object_intersection(type);
	return (object);
}
