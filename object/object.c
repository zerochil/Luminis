/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:27:08 by inajah            #+#    #+#             */
/*   Updated: 2025/03/11 15:05:46 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object.h>
#include "_object.h"

t_intersect object_intersection(enum e_object type)
{
	if (type == SPHERE)
		return (intersect_sphere);
	if (type == PLANE)
		return (intersect_plane);
	if (type == CYLINDER)
		return (intersect_cylinder);
	if (type == CONE)
		return (intersect_cone);
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
