/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:33:51 by inajah            #+#    #+#             */
/*   Updated: 2025/04/14 15:22:02 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATH_H
# define LIBMATH_H

# include <math.h>
# include <matrix.h>
# include <quadratic_eq.h>
# include <vec3.h>

# define EPSILON 1e-6

double	min(double a, double b);
double	max(double a, double b);
bool	float_eq(double a, double b);

#endif
