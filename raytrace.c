#include "raytrace.h"

t_hit find_intersection(t_scene *scene, t_ray *ray)
{
	t_hit closest_hit;
	t_object *object;
	t_array *objects;
	t_hit hit;
	size_t i;

	objects = scene->objects;
	hit.object = NULL;
	hit.distance = INFINITY;
	i = 0;
	while (i < objects->size)
	{
		object = array_get(objects, i);
		if (object->intersect(object, ray, &closest_hit))
		{
			if (closest_hit.distance < hit.distance)
				hit = closest_hit;
		}
		i++;
	}
	return (hit);
}

bool is_shadowed(t_scene *scene, t_ray ray, double light_distance)
{
	t_hit hit = find_intersection(scene, &ray);
	return (hit.object && hit.distance < light_distance);
}

t_color shade(t_scene *scene, t_ray *ray, t_hit *hit);

t_color calculate_lighting(t_scene *scene, t_ray *ray, t_hit *hit)
{
	size_t i;
	t_light *light;
	t_ray shadow_ray;
	double light_distance;

	i = 0;
	while (i < scene->lights->size)
	{
		light = array_get(scene->lights, i); // can this ever segfault if lights is empty?
		shadow_ray = (t_ray){
			.origin = hit->point,
			.direction = vec3_sub(light->origin, hit->point),
		};
		light_distance = vec3_length(shadow_ray.direction);
		if (is_shadowed(scene, shadow_ray, light_distance) == false)
		{
			t_color color = brdfs(hit->normal, vec3_negate(ray->direction), vec3_normalize(shadow_ray.direction), hit->object->material);
			t_color light_color = light->color;
			color_mul(&color, &light_color);
			// this here is whack; for tommorrow....
		}
		i++;
	}
}

t_color trace_ray(t_scene *scene, t_ray *ray, int depth)
{
	t_hit hit;
	t_color color;
	t_ray reflected_ray;
	t_color reflected_color;

	if (depth == 0)
		return ((t_color){0, 0, 0});
	hit = find_intersection(scene, ray);
	if (hit.object)
	{
		color = shade(scene, ray, &hit);
		reflected_ray = (t_ray){
			.origin = hit.point,
			.direction = vec3_reflect(vec3_negate(ray->direction), hit.normal),
		};
		reflected_color = trace_ray(scene, &reflected_ray, depth - 1);
		color_add(&color, &reflected_color);
		return (color);
	}
}
