/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _object.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:26:36 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/15 16:19:14 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _OBJECT_H
# define _OBJECT_H

# include <object.h>

typedef struct s_cone_uv_data
{
	t_uv	uv;
	t_vec3	apex;
	t_vec3	axis;
	double	height;
	t_vec3	local_p;
	double	proj;
	t_vec3	proj_vec;
	t_vec3	radial;
	double	radial_len;
	t_vec3	u;
	t_vec3	v;
	double	theta;
}	t_cone_uv_data;

typedef struct s_cylinder_uv_data
{
	t_vec3	proj;
	t_vec3	local_p;
	t_vec3	cx;
	t_vec3	cy;
	t_vec3	cz;
	t_uv	uv;
}	t_cylinder_uv_data;

bool		intersect_plane(t_object *obj, t_ray *ray, t_hit *hit);
bool		intersect_sphere(t_object *obj, t_ray *ray, t_hit *hit);
bool		intersect_cylinder(t_object *obj, t_ray *ray, t_hit *hit);
bool		intersect_cone(t_object *obj, t_ray *ray, t_hit *hit);

t_uv		get_plane_uv(t_hit *hit);
t_uv		get_sphere_uv(t_hit *hit);
t_uv		get_cylinder_uv(t_hit *hit);
t_uv		get_cone_uv(t_hit *hit);

#endif
