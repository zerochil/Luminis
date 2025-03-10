/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_eq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:28:00 by inajah            #+#    #+#             */
/*   Updated: 2025/03/10 15:29:00 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <quadratic_eq.h>

double quadratic_delta(t_quadratic_terms *qterms)
{
	qterms->delta = qterms->b * qterms->b - 4 * qterms->a * qterms->c;
	return (qterms->delta);
}

int quadratic_roots(t_quadratic_terms *qterms)
{
	double denom;

	denom = 1 / (2.0 * qterms->a);
	qterms->t1 = (-qterms->b - sqrt(qterms->delta)) * denom;
	qterms->t2 = (-qterms->b + sqrt(qterms->delta)) * denom;
	if (qterms->t1 <= 0 && qterms->t2 <= 0)
		return (-1);
	return (1);
}