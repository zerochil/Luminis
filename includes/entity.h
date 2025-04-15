/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:53:13 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/15 13:05:56 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include <object.h>

typedef struct s_light
{
	t_vec3	origin;
	double	intensity;
	t_vec3	color;
}			t_light;

typedef struct s_ambient
{
	double	intensity;
	t_vec3	color;
	bool	is_declared;
}			t_ambient;

typedef struct s_camera
{
	t_matrix view;
	t_vec3	origin;
	t_vec3	forward;
	t_vec3	up;
	t_vec3	right;
	double	fov;
	double	scale;
	double	ratio;
	bool	is_declared;
}			t_camera;

#endif
