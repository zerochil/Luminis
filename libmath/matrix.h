/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:21:59 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 15:30:46 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vec3.h"

typedef struct s_matrix
{
	double	data[16];
}			t_matrix;

t_matrix	matrix_identity(void);
t_matrix	matrix_translate(t_vec3 v);
t_matrix	matrix_multiply(t_matrix a, t_matrix b);
t_matrix	matrix_rotate(t_vec3 u, t_vec3 v, t_vec3 w);
t_vec3		vec3_mul_matrix(t_vec3 v, t_matrix mat);

#endif
