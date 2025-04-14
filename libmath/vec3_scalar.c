/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scalar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:38:17 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 15:38:22 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_vec3	vec3_add_scalar(t_vec3 a, double b)
{
	t_vec3	result;

	result.x = a.x + b;
	result.y = a.y + b;
	result.z = a.z + b;
	return (result);
}

t_vec3	vec3_sub_scalar(t_vec3 a, double b)
{
	t_vec3	result;

	result.x = a.x - b;
	result.y = a.y - b;
	result.z = a.z - b;
	return (result);
}

t_vec3	vec3_mul_scalar(t_vec3 a, double b)
{
	t_vec3	result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return (result);
}

t_vec3	vec3_div_scalar(t_vec3 a, double b)
{
	t_vec3	result;

	if (b == 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		return (result);
	}
	result.x = a.x / b;
	result.y = a.y / b;
	result.z = a.z / b;
	return (result);
}
