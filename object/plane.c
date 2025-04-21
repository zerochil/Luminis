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

t_uv	get_plane_uv(t_hit *hit)
{
	t_uv	uv;
	t_vec3	p_local;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	normal;

	normal = hit->object->orientation;
	p_local = vec3_sub(hit->point, hit->object->origin);
	create_orthonormal_basis(normal, &tangent, &bitangent);
	uv.u = fmod(vec3_dot(p_local, tangent) / 200, 1);
	uv.v = fmod(vec3_dot(p_local, bitangent) / 200, 1);
	return (uv);
}

bool	is_point_within_rectangle(t_object *obj, t_ray *ray, double t)
{
	t_vec3 point;
	t_vec3 u;
	t_vec3 v;
	t_uv uv;

	if (obj->width < 0 || obj->height < 0) //for infinit plane
		return (true);

	create_orthonormal_basis(obj->orientation, &u, &v);
	point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, t));
	point = vec3_sub(point, obj->origin);
	uv.u = vec3_dot(point, u);
	uv.v = vec3_dot(point, v);
	return (fabs(uv.u) < obj->width && fabs(uv.v) < obj->height);
}

bool	intersect_plane(t_object *object, t_ray *ray, t_hit *hit)
{
	double	t;
	double	denominator;
	t_vec3	normal;
	t_vec3	position;

	normal = object->orientation;
	denominator = vec3_dot(normal, ray->direction);
	if (float_eq(denominator, 0))
		return (false);
	position = vec3_sub(object->origin, ray->origin);
	t = vec3_dot(position, normal) / denominator;
	if (t <= 0)
		return (false);
	if (!is_point_within_rectangle(object, ray, t))
		return (false);
	hit->distance = t;
	hit->normal = vec3_negate_conditionally((denominator > 0), normal);
	hit->object = object;
	hit->point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, t));
	return (true);
}
