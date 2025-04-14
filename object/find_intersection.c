/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:49:31 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 11:49:36 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object.h>
#include <scene.h>

t_hit	find_intersection(t_scene *scene, t_ray *ray)
{
	t_hit		closest_hit;
	t_object	*object;
	t_array		*objects;
	t_hit		hit;
	size_t		i;

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
