/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:48:30 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/17 19:48:53 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	parse_float(double *value, char *str);

bool	parse_vec3(t_vec3 *vec, char *str)
{
	char	**components;

	components = ft_split(str, ',');
	resource_track(components, free_strings);
	if (!components || ft_strarr_len(components) != 3)
		return (false);
	if (parse_float(&vec->x, components[0]) == false)
		return (false);
	if (parse_float(&vec->y, components[1]) == false)
		return (false);
	if (parse_float(&vec->z, components[2]) == false)
		return (false);
	return (true);
}

bool	parse_vec3_interval(t_vec3 *vec, char *str, double min, double max)
{
	if (parse_vec3(vec, str) == false)
		return (parser_error("Orientation must be a vec3"));
	if (in_interval(vec->x, min, max) == false
		|| in_interval(vec->y, min, max) == false
		|| in_interval(vec->z, min, max) == false)
		return (parser_error("Orientation (x, y, z) must be in range [-1,1]"));
	return (true);
}

static bool	parse_color_channel(double *value, char *str)
{
	int	result;

	if (*str < '0' || *str > '9')
		return (false);
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		if (result > 255)
			return (false);
		str++;
	}
	if (*str != '\0')
		return (false);
	*value = result;
	return (true);
}

bool	parse_color(t_vec3 *color, char *str)
{
	char	**channels;

	channels = ft_split(str, ',');
	resource_track(channels, free_strings);
	if (!channels || ft_strarr_len(channels) != 3)
		return (false);
	if (parse_color_channel(&color->x, channels[0]) == false)
		return (false);
	if (parse_color_channel(&color->y, channels[1]) == false)
		return (false);
	if (parse_color_channel(&color->z, channels[2]) == false)
		return (false);
	color->x /= 255;
	color->y /= 255;
	color->z /= 255;
	return (true);
}

bool	parse_string(char **dest, char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == false)
			return (false);
		i++;
	}
	*dest = str;
	return (true);
}
