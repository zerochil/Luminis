/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:52:44 by inajah            #+#    #+#             */
/*   Updated: 2025/04/16 09:55:50 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_object.h"

t_uv	get_cylinder_uv(t_hit *hit)
{
	t_cylinder_uv_data	d;

	d.local_p = vec3_sub(hit->point, hit->object->origin);
	d.cz = hit->object->orientation;
	create_orthonormal_basis(d.cz, &d.cx, &d.cy);
	d.proj.x = vec3_dot(d.local_p, d.cx);
	d.proj.y = vec3_dot(d.local_p, d.cy);
	d.proj.z = vec3_dot(d.local_p, d.cz);
	d.uv.v = d.proj.z / hit->object->height + 0.5f;
	d.uv.u = (atan2(d.proj.y, d.proj.x) + M_PI) / (2 * M_PI) + 0.5f;
	return (d.uv);
}

static bool	is_point_within_cylinder_height(t_object *object, t_ray *ray,
		double t)
{
	t_vec3	hit_point;
	double	height;
	double	h;

	if (t < 0)
		return (false);
	h = object->height / 2;
	hit_point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, t));
	height = vec3_dot(vec3_sub(hit_point, object->origin), object->orientation);
	if (height < -h || height > h)
		return (false);
	return (true);
}

static t_quadratic_terms	cylinder_quadratic_terms(t_object *obj, t_ray *ray)
{
	t_quadratic_terms	qterms;
	t_vec3				v;
	t_vec3				co;
	t_vec3				d_perp;
	t_vec3				co_perp;

	v = obj->orientation;
	co = vec3_sub(ray->origin, obj->origin);
	d_perp = vec3_sub(ray->direction, vec3_mul_scalar(v,
				vec3_dot(ray->direction, v)));
	co_perp = vec3_sub(co, vec3_mul_scalar(v, vec3_dot(co, v)));
	qterms.a = vec3_dot(d_perp, d_perp);
	qterms.b = 2 * vec3_dot(co_perp, d_perp);
	qterms.c = vec3_dot(co_perp, co_perp) - (obj->radius * obj->radius);
	return (qterms);
}

static double	cylinder_solution(t_quadratic_terms qterms, t_object *obj,
		t_ray *ray)
{
	if (qterms.t1 < qterms.t2 && is_point_within_cylinder_height(obj, ray,
			qterms.t1))
		return (qterms.t1);
	if (is_point_within_cylinder_height(obj, ray, qterms.t2))
		return (qterms.t2);
	else
		return (-1);
}

bool	intersect_cylinder(t_object *obj, t_ray *ray, t_hit *hit)
{
	t_quadratic_terms	qterms;
	double				height_proj;
	bool				is_ray_inside;

	qterms = cylinder_quadratic_terms(obj, ray);
	if (quadratic_delta(&qterms) < 0)
		return (false);
	if (quadratic_roots(&qterms) < 0)
		return (false);
	hit->distance = cylinder_solution(qterms, obj, ray);
	if (hit->distance < 0)
		return (false);
	hit->point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction,
				hit->distance));
	height_proj = vec3_dot(vec3_sub(hit->point, obj->origin), obj->orientation);
	hit->normal = vec3_normalize(vec3_sub(hit->point, vec3_add(obj->origin,
					vec3_mul_scalar(obj->orientation, height_proj))));
	is_ray_inside = vec3_dot(vec3_sub(ray->origin, obj->origin),
			hit->normal) < obj->radius;
	hit->normal = vec3_negate_conditionally(is_ray_inside
			|| hit->distance == qterms.t2, hit->normal);
	hit->object = obj;
	return (true);
}
