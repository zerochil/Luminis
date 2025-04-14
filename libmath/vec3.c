/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:21:59 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 15:37:52 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_vec3	vec3_negate(t_vec3 a)
{
	t_vec3	result;

	result.x = -a.x;
	result.y = -a.y;
	result.z = -a.z;
	return (result);
}

t_vec3	vec3_negate_conditionally(bool condition, t_vec3 vec)
{
	if (condition)
		return (vec3_negate(vec));
	return (vec);
}

bool	vec3_compare(t_vec3 a, t_vec3 b)
{
	return (float_eq(a.x, b.x) && float_eq(a.y, b.y) && float_eq(a.z, b.z));
}

t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
{
	return (vec3_sub(v, vec3_mul_scalar(n, 2 * vec3_dot(v, n))));
}

t_vec3	vec3_lerp(t_vec3 a, t_vec3 b, double t)
{
	return (vec3_add(vec3_mul_scalar(a, 1 - t), vec3_mul_scalar(b, t)));
}
