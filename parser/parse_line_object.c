/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:58:15 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/17 19:51:13 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	parse_line_sphere(t_scene *scene, char **infos)
{
	t_object	*object;

	if (ft_strarr_len(infos) < 4 || ft_strarr_len(infos) > 5)
		return (parser_error("Sphere must have 4 or 3 arguments"));
	object = object_create(SPHERE);
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (parser_error("Sphere origin must be a vec3"));
	if (parse_float(&object->radius, infos[2]) == false)
		return (parser_error("Sphere radius must be a float"));
	if (parse_color(&object->color, infos[3]) == false)
		return (parser_error("Sphere color must be a color"));
	if (in_interval(object->radius, 0, INFINITY) == false)
		return (parser_error("Sphere radius must be positive"));
	if (infos[4] && parse_string(&object->texture_name, infos[4]) == false)
		return (parser_error("Texture name isn't composed of only characters"));
	object->radius /= 2;
	array_push(scene->objects, object);
	return (true);
}

bool	parse_line_plane(t_scene *scene, char **infos)
{
	t_object	*object;

	if (ft_strarr_len(infos) < 4 || ft_strarr_len(infos) > 5)
		return (parser_error("Plane must have 3 or 4 arguments"));
	object = object_create(PLANE);
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (parser_error("Plane origin must be a vec3"));
	if (parse_vec3_interval(&object->orientation, infos[2], -1, 1) == false)
		return (false);
	if (parse_color(&object->color, infos[3]) == false)
		return (parser_error("Plane color must be a color"));
	object->orientation = vec3_normalize(object->orientation);
	if (vec3_length(object->orientation) == 0)
		return (parser_error("Plane normal must be a non-zero vector"));
	if (infos[4] && parse_string(&object->texture_name, infos[4]) == false)
		return (parser_error("Texture name isn't composed of only characters"));
	array_push(scene->objects, object);
	return (true);
}


bool	parse_line_rectangle(t_scene *scene, char **infos)
{
	t_object	*object;

	if (ft_strarr_len(infos) < 6 || ft_strarr_len(infos) > 7)
		return (parser_error("Rectangle must have 3 or 4 arguments"));
	object = object_create(PLANE);
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (parser_error("Rectangle origin must be a vec3"));
	if (parse_vec3_interval(&object->orientation, infos[2], -1, 1) == false)
		return (false);
	object->orientation = vec3_normalize(object->orientation);
	if (vec3_length(object->orientation) == 0)
		return (parser_error("Rectangle normal must be a non-zero vector"));
	if (parse_float(&object->width, infos[3]) == false)
		return (parser_error("Rectangle width must be a float"));
	if (parse_float(&object->height, infos[4]) == false)
		return (parser_error("Rectangle height must be a float"));
	if (parse_color(&object->color, infos[5]) == false)
		return (parser_error("Rectangle color must be a color"));
	if (infos[6] && parse_string(&object->texture_name, infos[6]) == false)
		return (parser_error("Texture name isn't composed of only characters"));
	object->width /= 2;
	object->height /= 2;
	array_push(scene->objects, object);
	return (true);
}

bool	parse_line_cylinder(t_scene *scene, char **infos)
{
	t_object	*object;

	if (ft_strarr_len(infos) < 6 || ft_strarr_len(infos) > 7)
		return (parser_error("Cylinder must have 5 or 6 arguments"));
	object = object_create(CYLINDER);
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (parser_error("Cylinder origin must be a vec3"));
	if (parse_vec3_interval(&object->orientation, infos[2], -1, 1) == false)
		return (false);
	if (parse_float(&object->radius, infos[3]) == false)
		return (parser_error("Cylinder radius must be a float"));
	if (parse_float(&object->height, infos[4]) == false)
		return (parser_error("Cylinder height must be a float"));
	if (parse_color(&object->color, infos[5]) == false)
		return (parser_error("Cylinder color must be a color"));
	if (infos[6] && parse_string(&object->texture_name, infos[6]) == false)
		return (parser_error("Texture name isn't composed of only characters"));
	if (in_interval(object->radius, 0, INFINITY) == false)
		return (parser_error("Cylinder radius must be positive"));
	if (in_interval(object->height, 0, INFINITY) == false)
		return (parser_error("Cylinder height must be positive"));
	object->orientation = vec3_normalize(object->orientation);
	if (vec3_length(object->orientation) == 0)
		return (parser_error("Plane normal must be a non-zero vector"));
	return (object->radius /= 2, array_push(scene->objects, object), true);
}

bool	validate_cone(t_object *object)
{
	if (in_interval(object->height, 0, INFINITY) == false)
		return (parser_error("Cone height must be positive"));
	if (in_interval(object->angle, 0, 90) == false)
		return (parser_error("Cone opening angle must be in range [0, 90]"));
	if (vec3_length(object->orientation) == 0)
		return (parser_error("Plane normal must be a non-zero vector"));
	return (true);
}

bool	parse_line_cone(t_scene *scene, char **infos)
{
	t_object	*object;

	if (ft_strarr_len(infos) < 6 || ft_strarr_len(infos) > 7)
		return (parser_error("Cone must have 4 or 5 arguments"));
	object = object_create(CONE);
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (parser_error("Cone origin must be a vec3"));
	if (parse_vec3_interval(&object->orientation, infos[2], -1, 1) == false)
		return (false);
	if (parse_float(&object->angle, infos[3]) == false)
		return (parser_error("Cone opening angle must be a float"));
	if (parse_float(&object->height, infos[4]) == false)
		return (parser_error("Cone height must be a float"));
	if (parse_color(&object->color, infos[5]) == false)
		return (parser_error("Cone color must be a color"));
	if (infos[6] && parse_string(&object->texture_name, infos[6]) == false)
		return (parser_error("Texture name isn't composed of characters"));
	object->orientation = vec3_normalize(object->orientation);
	if (validate_cone(object) == false)
		return (false);
	object->angle /= 2;
	array_push(scene->objects, object);
	return (true);
}
