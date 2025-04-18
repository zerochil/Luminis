/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_meta.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:57:05 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/18 08:04:05 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	parse_line_ambient(t_scene *scene, char **infos)
{
	if (ft_strarr_len(infos) != 3)
		return (parser_error("Ambient light must have 2 arguments"));
	if (scene->ambient.is_declared)
		return (parser_error("Ambient light already declared"));
	if (parse_float(&scene->ambient.intensity, infos[1]) == false)
		return (parser_error("Ambient light intensity must be a float"));
	if (parse_color(&scene->ambient.color, infos[2]) == false)
		return (parser_error("Ambient light color must be a color"));
	if (in_interval(scene->ambient.intensity, 0, 1) == false)
		return (parser_error("Ambient light intensity isn't between 0 and 1"));
	scene->ambient.is_declared = true;
	return (true);
}

bool	parse_line_camera(t_scene *scene, char **infos)
{
	if (ft_strarr_len(infos) != 4)
		return (parser_error("Camera must have 3 arguments"));
	if (scene->camera.is_declared)
		return (parser_error("Camera already declared"));
	if (parse_vec3(&scene->camera.origin, infos[1]) == false)
		return (parser_error("Camera origin must be a vec3"));
	if (parse_vec3_interval(&scene->camera.forward, infos[2], -1, 1) == false)
		return (false);
	if (parse_float(&scene->camera.fov, infos[3]) == false)
		return (parser_error("Camera fov must be a float"));
	if (in_interval(scene->camera.fov, 0, 180) == false)
		return (parser_error("Camera fov must be between 0 and 180"));
	scene->camera.forward = vec3_normalize(scene->camera.forward);
	if (is_normalized(scene->camera.forward) == false)
		return (parser_error("Camera direction must be normalized"));
	if (scene->camera.forward.y > 0.9 || scene->camera.forward.y < -0.9)
		scene->camera.right = vec3_cross(scene->camera.forward, (t_vec3){0, 0,
				1});
	else
		scene->camera.right = vec3_cross(scene->camera.forward, (t_vec3){0, 1,
				0});
	scene->camera.up = vec3_cross(scene->camera.right, scene->camera.forward);
	scene->camera.is_declared = true;
	return (true);
}

bool	parse_line_light(t_scene *scene, char **infos)
{
	t_light	*light;

	if (ft_strarr_len(infos) != 4)
		return (parser_error("Light must have 3 arguments"));
	light = track_malloc(sizeof(t_light));
	if (parse_vec3(&light->origin, infos[1]) == false)
		return (parser_error("Light origin must be a vec3"));
	if (parse_float(&light->intensity, infos[2]) == false)
		return (parser_error("Light intensity must be a float"));
	if (parse_color(&light->color, infos[3]) == false)
		return (parser_error("Light color must be a color"));
	if (in_interval(light->intensity, 0, 1) == false)
		return (parser_error("Light intensity must be between 0 and 1"));
	light->origin = vec3_add_scalar(light->origin, 0.1);
	array_push(scene->lights, light);
	return (true);
}
