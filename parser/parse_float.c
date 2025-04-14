/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:09:15 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 15:17:45 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static bool	parse_float_decimal(double *value, char **str)
{
	if (**str < '0' || **str > '9')
		return (false);
	while (**str >= '0' && **str <= '9')
	{
		if (*value > DBL_MAX / 10.0
			|| (*value == DBL_MAX / 10.0 && **str - '0' > fmod(DBL_MAX, 10.0)))
			return (false);
		*value *= 10;
		*value += **str - '0';
		(*str)++;
	}
	return (true);
}

static bool	parse_float_fractional(double *value, char **str)
{
	double	decimal_place;

	if (**str != '.')
		return (true);
	(*str)++;
	if (**str < '0' || **str > '9')
		return (false);
	decimal_place = 0.1;
	while (**str >= '0' && **str <= '9')
	{
		if (DBL_MAX - decimal_place * (**str - '0') < *value)
			return (false);
		*value += (**str - '0') * decimal_place;
		decimal_place *= 0.1;
		(*str)++;
	}
	return (true);
}

bool	parse_float(double *value, char *str)
{
	double	sign;

	sign = 1;
	*value = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (parse_float_decimal(value, &str) == false)
		return (false);
	if (parse_float_fractional(value, &str) == false)
		return (false);
	if (*str != '\0')
		return (false);
	*value *= sign;
	return (true);
}
