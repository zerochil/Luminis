/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:38:51 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/15 15:45:57 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

void	rotate(t_vec3 *vec, t_vec3 axis, double angle)
{
	double	sin_half;
	double	cos_half;
	t_vec3	qv;
	t_vec3	t;
	t_vec3	u;

	angle *= M_PI / 180.0;
	sin_half = sin(angle / 2);
	cos_half = cos(angle / 2);
	qv = (t_vec3){axis.x * sin_half, axis.y * sin_half, axis.z * sin_half};
	t.x = qv.y * vec->z - qv.z * vec->y;
	t.y = qv.z * vec->x - qv.x * vec->z;
	t.z = qv.x * vec->y - qv.y * vec->x;
	u.x = qv.y * t.z - qv.z * t.y;
	u.y = qv.z * t.x - qv.x * t.z;
	u.z = qv.x * t.y - qv.y * t.x;
	vec->x += 2 * cos_half * t.x + 2 * u.x;
	vec->y += 2 * cos_half * t.y + 2 * u.y;
	vec->z += 2 * cos_half * t.z + 2 * u.z;
}

void	create_orthonormal_basis(t_vec3 n, t_vec3 *b1, t_vec3 *b2)
{
	float	a;
	float	b;

	if (n.z < -0.9999999)
	{
		*b1 = (t_vec3){1.0, 0.0, 0.0};
		*b2 = (t_vec3){0.0, 1.0, 0.0};
		return ;
	}
	a = 1.0 / (1.0 + n.z);
	b = -n.x * n.y * a;
	*b1 = (t_vec3){1.0 - n.x * n.x * a, b, -n.x};
	*b2 = (t_vec3){b, 1.0 - n.y * n.y * a, -n.y};
}
