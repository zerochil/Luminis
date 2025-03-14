/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:33:51 by inajah            #+#    #+#             */
/*   Updated: 2025/03/10 15:57:35 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATH_H
#define LIBMATH_H

# include <math.h>
# include <quadratic_eq.h>
# include <vec3.h>
# include <matrix.h>

# define EPSILON 1e-6

double	min(double a, double b);
double	max(double a, double b);
bool	float_eq(double a, double b);

#endif