/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:38:28 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 11:38:30 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lighting.h>

static bool	is_shadowed(t_scene *scene, t_light *light, t_hit *hit)
{
	t_ray	shadow_ray;
	double	light_distance;
	t_hit	light_hit;

	shadow_ray = (t_ray){
		.origin = vec3_add(hit->point, vec3_mul_scalar(hit->normal, EPSILON
				* 10000)),
		.direction = vec3_sub(light->origin, hit->point),
	};
	light_distance = vec3_length(shadow_ray.direction);
	shadow_ray.direction = vec3_mul_scalar(shadow_ray.direction, 1
			/ light_distance);
	light_hit = find_intersection(scene, &shadow_ray);
	return (light_hit.object && light_hit.distance < light_distance);
}

static void	color_clamp(t_vec3 *color)
{
	color->x = fmin(fmax(color->x, 0.0), 1.0);
	color->y = fmin(fmax(color->y, 0.0), 1.0);
	color->z = fmin(fmax(color->z, 0.0), 1.0);
}

static t_vec3	calculate_ambient(t_scene *scene, t_hit *hit)
{
	t_vec3	color;
	t_vec3	ambient;

	color = hit->object->texture->evaluate(hit->object->texture, hit);
	ambient = scene->ambient.color;
	ambient = vec3_mul_scalar(ambient, scene->ambient.intensity);
	ambient = vec3_mul(ambient, color);
	return (ambient);
}

static void	calculate_light_color(t_light_data d, t_hit *hit, t_scene *scene,
		t_vec3 *total_light)
{
	d.light_dir = vec3_normalize(vec3_sub(d.light->origin, hit->point));
	d.diffuse_intensity = fmax(vec3_dot(hit->normal, d.light_dir), 0.0);
	if (d.diffuse_intensity > 0.0)
	{
		d.light_dist = vec3_length(vec3_sub(d.light->origin, hit->point));
		d.attenuation = 1.0 / (1.0 + 0.0001 * d.light_dist * d.light_dist);
		d.intensity = d.light->intensity * d.attenuation;
		d.light_color = d.light->color;
		d.light_color = vec3_mul(d.light_color, d.obj_color);
		d.light_color = vec3_mul_scalar(d.light_color, d.intensity);
		d.light_color = vec3_mul_scalar(d.light_color, d.diffuse_intensity * 1);
		*total_light = vec3_add(*total_light, d.light_color);
		d.reflect_dir = vec3_reflect(vec3_negate(d.light_dir), hit->normal);
		d.view_dir = vec3_normalize(vec3_sub(scene->camera.origin, hit->point));
		d.specular = (t_vec3){1.0, 1.0, 1.0};
		d.specular = vec3_mul_scalar(d.specular, d.intensity);
		d.specular = vec3_mul_scalar(d.specular, pow(fmax(vec3_dot(d.view_dir,
							d.reflect_dir), 0.0), 50.0));
		d.specular = vec3_mul_scalar(d.specular, 0.9);
		*total_light = vec3_add(*total_light, d.specular);
	}
}

t_vec3	calculate_lighting(t_scene *scene, t_hit *hit)
{
	t_vec3			total_light;
	t_array			*lights;
	t_light_data	data;
	size_t			i;

	i = 0;
	lights = scene->lights;
	total_light = calculate_ambient(scene, hit);
	data.obj_color = hit->object->texture->evaluate(hit->object->texture, hit);
	hit->point = vec3_add(hit->point, vec3_mul_scalar(hit->normal, EPSILON
				* 10000));
	while (i < lights->size)
	{
		data.light = array_get(lights, i);
		i++;
		if (is_shadowed(scene, data.light, hit))
			continue ;
		calculate_light_color(data, hit, scene, &total_light);
	}
	data.obj_color = total_light;
	color_clamp(&data.obj_color);
	return (vec3_mul_scalar(data.obj_color, 255.0));
}
