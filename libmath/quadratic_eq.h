/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_eq.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:29:29 by inajah            #+#    #+#             */
/*   Updated: 2025/04/14 15:22:03 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRATIC_EQ_H
# define QUADRATIC_EQ_H

# include <math.h>

typedef struct s_quadratic_terms
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t1;
	double	t2;
	double	denominator;
}			t_quadratic_terms;

double		quadratic_delta(t_quadratic_terms *qterms);
int			quadratic_roots(t_quadratic_terms *qterms);

#endif
