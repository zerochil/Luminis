/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:21:59 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 15:22:02 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

double	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

bool	float_eq(double a, double b)
{
	return (fabs(a - b) < EPSILON * fmax(fabs(a), fabs(b)));
}
