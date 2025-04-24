/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:27:08 by inajah            #+#    #+#             */
/*   Updated: 2025/04/15 15:59:59 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_object.h"
#include <object.h>

t_intersect	object_intersection(enum e_object type)
{
	if (type == SPHERE)
		return (intersect_sphere);
	if (type == PLANE)
		return (intersect_plane);
	if (type == RECTANGLE)
		return (intersect_rectangle);
	if (type == CYLINDER)
		return (intersect_cylinder);
	if (type == CONE)
		return (intersect_cone);
	return (NULL);
}

t_object_uv	object_uv(enum e_object type)
{
	if (type == SPHERE)
		return (get_sphere_uv);
	if (type == PLANE || type == RECTANGLE)
		return (get_plane_uv);
	if (type == CYLINDER)
		return (get_cylinder_uv);
	if (type == CONE)
		return (get_cone_uv);
	return (NULL);
}

t_object	*object_create(enum e_object type)
{
	t_object	*object;

	object = track_malloc(sizeof(t_object));
	object->type = type;
	object->intersect = object_intersection(type);
	object->get_uv = object_uv(type);
	object->texture_name = NULL;
	return (object);
}


void print_vec3(t_vec3 v)
{
	printf("%.6g,%.6g,%.6g", v.x, v.y, v.z);
}

void print_color(t_vec3 color)
{
	printf("%d,%d,%d", (int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255));
}

void print_object(t_object *obj)
{
	if (!obj)
		return;

	switch (obj->type)
	{
	case SPHERE:
		// sp <origin> <diameter> <color>
		printf("sp ");
		print_vec3(obj->origin);
		printf(" %.6g ", obj->radius * 2);
		print_color(obj->color);
		break;

	case PLANE:
		// pl <origin> <normal> <color>
		printf("pl ");
		print_vec3(obj->origin);
		printf(" ");
		print_vec3(obj->orientation);
		printf(" ");
		print_color(obj->color);
		break;

	case CYLINDER:
		// cy <origin> <axis> <diameter> <height> <color>
		printf("cy ");
		print_vec3(obj->origin);
		printf(" ");
		print_vec3(obj->orientation);
		printf(" %.6g %.6g ", obj->radius, obj->height);
		print_color(obj->color);
		break;

	case CONE:
		// co <origin> <axis> <angle> <height> <color>
		printf("co ");
		print_vec3(obj->origin);
		printf(" ");
		print_vec3(obj->orientation);
		printf(" %.6g %.6g ", obj->angle, obj->height);
		print_color(obj->color);
		break;

	case RECTANGLE:
		// re <origin> <orientation> <width> <height> <color>
		printf("rec ");
		print_vec3(obj->origin);
		printf(" ");
		print_vec3(obj->orientation);
		printf(" %.6g %.6g ", obj->width * 2, obj->height * 2);
		print_color(obj->color);
		break;

	default:
		printf("Unknown object type\n");
		break;
	}

	printf("\n");
}
