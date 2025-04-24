/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:00:22 by inajah            #+#    #+#             */
/*   Updated: 2025/04/15 16:00:23 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_object.h"

bool	is_point_within_rectangle(t_object *obj, t_vec3 point)
{
	t_vec3 local_p;
	t_vec3 u;
	t_vec3 v;
	t_uv uv;

	create_orthonormal_basis(obj->orientation, &u, &v);
	local_p = vec3_sub(point, obj->origin);
	uv.u = vec3_dot(local_p, u);
	uv.v = vec3_dot(local_p, v);
	return (fabs(uv.u) < obj->width && fabs(uv.v) < obj->height);
}

bool	intersect_rectangle(t_object *object, t_ray *ray, t_hit *hit)
{
	return (intersect_plane(object, ray, hit)
		&& is_point_within_rectangle(object, hit->point));
}
