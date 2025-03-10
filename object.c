/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:27:08 by inajah            #+#    #+#             */
/*   Updated: 2025/03/10 15:57:54 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_vec3	flip_normal(bool condition, t_vec3 normal)
{
	if (condition)
		return (vec3_negate(normal));
	return (normal);
}

bool		intersect_plane(t_object *object, t_ray *ray, t_hit *hit)
{
	double t;
	double denominator;
	t_vec3 normal;
	t_vec3 position;

	normal = object->orientation;
	denominator = vec3_dot(normal, ray->direction);
	if (float_eq(denominator, 0))
		return (false);
	position = vec3_sub(object->origin, ray->origin);
	t = vec3_dot(position, normal) / denominator;
	if (t <= 0)
		return (false);
	hit->distance = t;
	hit->normal = flip_normal((denominator > 0), normal);
	hit->object = object;
	hit->point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, t));
	return (true);
}

bool	test(t_object *object, t_vec3 hit_point)
{
    double height_proj = vec3_dot(vec3_sub(hit_point, object->origin), object->orientation);
	if (height_proj < 0 || height_proj > object->height)
        return false;
	return true;
}

bool intersect_cylinder(t_object *object, t_ray *ray, t_hit *hit)
{
    t_vec3 V = object->orientation;
    t_vec3 CO = vec3_sub(ray->origin, object->origin);

    t_vec3 D_perp = vec3_sub(ray->direction, vec3_mul_scalar(V, vec3_dot(ray->direction, V)));
    t_vec3 CO_perp = vec3_sub(CO, vec3_mul_scalar(V, vec3_dot(CO, V)));

    double A = vec3_dot(D_perp, D_perp);
    double B = 2 * vec3_dot(CO_perp, D_perp);
    double C = vec3_dot(CO_perp, CO_perp) - (object->radius * object->radius);

    double discriminant = B * B - 4 * A * C;
    if (discriminant < 0)
        return false;

    double t1 = (-B - sqrt(discriminant)) / (2 * A);
    double t2 = (-B + sqrt(discriminant)) / (2 * A);
	if (t1 < 0 && t2 < 0)
		return false;
	t_vec3 hit_point;
	t_vec3 hit_point1 = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, t1));
	t_vec3 hit_point2 = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, t2));
	if (t1 < t2 && test(object, hit_point1))
	{
		hit_point = hit_point1;
		hit->distance = t1;
	}
	else if (test(object, hit_point2))
	{
		hit->distance = t2;
		hit_point = hit_point2;
	}
	else
		return false;
	double height_proj = vec3_dot(vec3_sub(hit_point, object->origin), object->orientation);
    hit->point = hit_point;
    hit->normal = vec3_normalize(vec3_sub(hit_point, vec3_add(object->origin, vec3_mul_scalar(V, height_proj))));
	hit->object = object;
    return true;
}

double sphere_solution(t_quadratic_terms qterms)
{
	if (qterms.t1 < 0)
		return (qterms.t2);
	else if (qterms.t2 < 0)
		return (qterms.t1);
	else
		return (fmin(qterms.t1, qterms.t2));
}

bool		intersect_sphere(t_object *object, t_ray *ray, t_hit *hit)
{
	t_quadratic_terms qterms;
	t_vec3 position;
	t_vec3 direction;

	direction = vec3_sub(ray->origin, object->origin);
	qterms.a = 1;
	qterms.b = 2 * vec3_dot(ray->direction, direction);
	qterms.c = vec3_dot(direction, direction) - object->radius * object->radius;
	if (quadratic_delta(&qterms) < 0)
		return (false);
	if (quadratic_roots(&qterms) < 0)
		return (false);
	hit->distance = sphere_solution(qterms);
	position = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, hit->distance));
	hit->normal = vec3_normalize(vec3_sub(position, object->origin));
	hit->normal = flip_normal(vec3_length(direction) <= object->radius, hit->normal);
	hit->object = object;
	hit->point = position;
	return (true);
}

t_quadratic_terms	cone_quadratic_terms(t_object *obj, t_ray *ray, double k2)
{
	//(x−xc​)^2+(y−yc​)^2+(z−zc​)^2 − (1+k2)((x−xc​) * vx​+ (y−yc​) * vy​ + (z−zc​) * vz​)^2=0
	t_quadratic_terms qterms;
	t_vec3 o;
	double dv;
	double ov;

	dv = vec3_dot(ray->direction, obj->orientation);
	o = vec3_sub(ray->origin, obj->origin);
	ov = vec3_dot(o, obj->orientation);
    qterms.a = vec3_dot(ray->direction, ray->direction) - (1 + k2) * (dv * dv);
    qterms.b = 2 * (vec3_dot(o, ray->direction) - (1 + k2) * (ov * dv));
    qterms.c = vec3_dot(o, o) - (1 + k2) * (ov * ov);
	return (qterms);
}

bool		intersect_cone(t_object *obj, t_ray *ray, t_hit *hit)
{
	t_quadratic_terms qterms;
	t_vec3 local_point;
	t_vec3 axis_comp;
	double k2;

	k2 = pow2(tan(obj->angle * (M_PI / 180)));
	qterms = cone_quadratic_terms(obj, ray, k2);
	if (quadratic_delta(&qterms) < 0)
		return (false);
	if (quadratic_roots(&qterms) < 0)
		return (false);
	hit->distance = sphere_solution(qterms);
	hit->point = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, hit->distance));
	local_point = vec3_sub(hit->point, obj->origin);
	axis_comp = vec3_mul_scalar(obj->orientation, 
		(1 + k2) * vec3_dot(obj->orientation, local_point));
	hit->normal = vec3_normalize(vec3_sub(local_point, axis_comp));	
	hit->normal = flip_normal(vec3_dot(hit->normal, ray->direction) > 0, hit->normal);
	hit->object = obj;
	return (true);
}

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
