/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:38:29 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/17 17:19:25 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <stdio.h>

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	vec3_length(t_vec3 a)
{
	double	dot;

	dot = a.x * a.x + a.y * a.y + a.z * a.z;
	return (sqrt(dot));
}

t_vec3	vec3_normalize(t_vec3 a)
{
	double	length;

	length = vec3_length(a);
	if (length == 0)
	{
		printf("Warning: Normalizing a zero vector\n");
		return (a);
	}
	return (vec3_mul_scalar(a, 1 / length));
}
