/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_predicates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:58:58 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 14:48:33 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	is_normalized(t_vec3 vec)
{
	return (float_eq(vec3_length(vec), 1));
}

bool	in_interval(double value, double min, double max)
{
	return (value >= min && value <= max);
}
