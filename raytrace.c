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

bool is_shadowed(t_scene *scene, t_light *light, t_hit *hit)
{
	t_ray shadow_ray;
	double light_distance;
	t_hit light_hit;

	shadow_ray = (t_ray){
		.origin = hit->point,
		.direction = vec3_sub(light->origin, hit->point),
	};
	light_distance = vec3_length(shadow_ray.direction);
	light_hit = find_intersection(scene, &shadow_ray);
	return (light_hit.object && light_hit.distance < light_distance);
}

t_vec3 shade(t_scene *scene, t_ray *ray, t_hit *hit);

t_vec3 calculate_lighting(t_scene *scene, t_ray *ray, t_hit *hit)
{
	size_t i;
	t_light *light;
	t_ray shadow_ray;

	i = 0;
	while (i < scene->lights->size)
	{
		light = array_get(scene->lights, i); // can this ever segfault if lights is empty?
		if (is_shadowed(scene, light, hit) == false)
		{
			t_vec3 color = brdfs(hit->normal, vec3_negate(ray->direction), vec3_normalize(shadow_ray.direction), hit->object->material);
			t_vec3 light_color = light->color;
			color = vec3_mul(color, light_color);
			// this here is whack; for tommorrow....
		}
		i++;
	}
}

t_vec3 trace_ray(t_scene *scene, t_ray *ray, int depth)
{
	t_hit hit;
	t_vec3 color;
	t_ray reflected_ray;
	t_vec3 reflected_color;

	if (depth == 0)
		return ((t_vec3){0, 0, 0});
	hit = find_intersection(scene, ray);
	if (hit.object)
	{
		color = shade(scene, ray, &hit);
		reflected_ray = (t_ray){
			.origin = hit.point,
			.direction = vec3_reflect(vec3_negate(ray->direction), hit.normal),
		};
		reflected_color = trace_ray(scene, &reflected_ray, depth - 1);
		color = vec3_add(color, reflected_color);
		return (color);
	}
}
