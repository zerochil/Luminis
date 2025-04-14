/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:21:59 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 15:30:51 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	matrix_identity(void)
{
	t_matrix	m;
	int			i;

	i = 0;
	while (i < 16)
	{
		m.data[i] = 0;
		i++;
	}
	m.data[0] = 1;
	m.data[5] = 1;
	m.data[10] = 1;
	m.data[15] = 1;
	return (m);
}

t_matrix	matrix_translate(t_vec3 v)
{
	t_matrix	m;

	m = matrix_identity();
	m.data[3] = v.x;
	m.data[7] = v.y;
	m.data[11] = v.z;
	return (m);
}

t_matrix	matrix_multiply(t_matrix a, t_matrix b)
{
	t_matrix	m;
	int			i;
	int			j;
	int			k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.data[i * 4 + j] = 0;
			k = 0;
			while (k < 4)
			{
				m.data[i * 4 + j] += a.data[i * 4 + k] * b.data[k * 4 + j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (m);
}

t_matrix	matrix_rotate(t_vec3 u, t_vec3 v, t_vec3 w)
{
	t_matrix	m;

	m = matrix_identity();
	m.data[0] = u.x;
	m.data[1] = u.y;
	m.data[2] = u.z;
	m.data[4] = v.x;
	m.data[5] = v.y;
	m.data[6] = v.z;
	m.data[8] = w.x;
	m.data[9] = w.y;
	m.data[10] = w.z;
	return (m);
}

t_vec3	vec3_mul_matrix(t_vec3 v, t_matrix mat)
{
	t_vec3	result;
	double	*m;

	m = mat.data;
	result.x = v.x * m[0] + v.y * m[4] + v.z * m[8];
	result.y = v.x * m[1] + v.y * m[5] + v.z * m[9];
	result.z = v.x * m[2] + v.y * m[6] + v.z * m[10];
	return (result);
}
