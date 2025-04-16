/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:52:09 by inajah            #+#    #+#             */
/*   Updated: 2025/04/16 15:32:03 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_object.h"

t_uv	get_cone_uv(t_hit *hit)
{
	t_cone_uv_data	d;

	d.apex = hit->object->origin;
	d.axis = hit->object->orientation;
	d.height = 100;
	d.local_p = vec3_sub(hit->point, d.apex);
	d.proj = vec3_dot(d.local_p, d.axis);
	d.proj_vec = vec3_mul_scalar(d.axis, d.proj);
	d.radial = vec3_sub(d.local_p, d.proj_vec);
	d.radial_len = vec3_length(d.radial);
	if (d.radial_len < EPSILON)
	{
		d.uv.u = 0.5;
		d.uv.v = fmod(1.0 - (d.proj / d.height), 1.0);
		return (d.uv);
	}
	d.radial = vec3_div_scalar(d.radial, d.radial_len);
	create_orthonormal_basis(d.axis, &d.u, &d.v);
	d.theta = atan2(vec3_dot(d.radial, d.v), vec3_dot(d.radial, d.u));
	d.uv.u = (d.theta + M_PI) / (2.0 * M_PI);
	d.uv.v = fmod(1.0 - (d.proj / d.height), 1.0);
	return (d.uv);
}

bool	is_point_within_cone_height(t_object *object, t_ray *ray,
		double t)
{
	t_vec3	hit_point;
	double	height;
	double	h;

	if (t < 0)
		return (false);
	h = object->height;
	hit_point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, t));
	height = vec3_dot(vec3_sub(hit_point, object->origin), object->orientation);
	if (height < 0 || height > h)
		return (false);
	return (true);
}

static double	cone_solution(t_quadratic_terms qterms, t_object *obj,
		t_ray *ray)
{
	double	t;

	if (qterms.t1 < 0 || qterms.t2 < 0)
	{
		t = fmax(qterms.t1, qterms.t2);
		if (is_point_within_cone_height(obj, ray, t))
			return (t);
	}
	t = fmin(qterms.t1, qterms.t2);
	if (is_point_within_cone_height(obj, ray, t))
		return (t);
	t = fmax(qterms.t1, qterms.t2);
	if (is_point_within_cone_height(obj, ray, t))
		return (t);
	return (-1);
}

static t_quadratic_terms	cone_quadratic_terms(t_object *obj, t_ray *ray,
		double k2)
{
	t_quadratic_terms	qterms;
	t_vec3				o;
	double				dv;
	double				ov;

	dv = vec3_dot(ray->direction, obj->orientation);
	o = vec3_sub(ray->origin, obj->origin);
	ov = vec3_dot(o, obj->orientation);
	qterms.a = vec3_dot(ray->direction, ray->direction) - (1 + k2) * (dv * dv);
	qterms.b = 2 * (vec3_dot(o, ray->direction) - (1 + k2) * (ov * dv));
	qterms.c = vec3_dot(o, o) - (1 + k2) * (ov * ov);
	return (qterms);
}

bool	intersect_cone(t_object *obj, t_ray *ray, t_hit *hit)
{
	t_quadratic_terms	qterms;
	t_vec3				local_point;
	t_vec3				axis_comp;
	double				k2;

	k2 = pow2(tan(obj->angle * (M_PI / 180)));
	qterms = cone_quadratic_terms(obj, ray, k2);
	if (quadratic_delta(&qterms) < 0)
		return (false);
	if (quadratic_roots(&qterms) < 0)
		return (false);
	hit->distance = cone_solution(qterms, obj, ray);
	if (hit->distance < 0)
		return (false);
	hit->point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction,
				hit->distance));
	local_point = vec3_sub(hit->point, obj->origin);
	axis_comp = vec3_mul_scalar(obj->orientation, (1 + k2)
			* vec3_dot(obj->orientation, local_point));
	hit->normal = vec3_normalize(vec3_sub(local_point, axis_comp));
	hit->normal = vec3_negate_conditionally(vec3_dot(hit->normal,
				ray->direction) > 0, hit->normal);
	hit->object = obj;
	return (true);
}
