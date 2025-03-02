#include "object.h"

bool		intersect_plane(t_object *object, t_ray *ray, t_hit *hit)
{
	(void)hit;
	(void)ray;
	(void)object;
	return (false);
}

bool		intersect_cylinder(t_object *object, t_ray *ray, t_hit *hit)
{
	(void)hit;
	(void)ray;
	(void)object;
	return (false);
}

bool		intersect_sphere(t_object *object, t_ray *ray, t_hit *hit)
{
	float b;
	float c;
	float delta;
	float t1;
	float t2;
	t_vec3 position;
	t_vec3 direction;

	direction = vec3_sub(ray->origin, object->origin);
	b = 2 * vec3_dot(ray->direction, direction);
	c = vec3_dot(direction, direction) - object->sphere.radius * object->sphere.radius;
	delta = b * b - 4 * c;
	if (delta < 0)
		return (false);
	t1 = (-b - sqrt(delta)) / 2;
	t2 = (-b + sqrt(delta)) / 2;
	if (t1 < 0 && t2 < 0)
		return (false);
	if (t1 < 0)
		hit->distance = t2;
	else if (t2 < 0)
		hit->distance = t1;
	else
		hit->distance = fmin(t1, t2);
	position = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, hit->distance));
	hit->normal = vec3_normalize(vec3_sub(position, object->origin));
	hit->object = object;
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
