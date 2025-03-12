#include <parser.h>

static bool parse_float_decimal(double *value, char **str)
{
	if (**str < '0' || **str > '9')
		return (false);
	while (**str >= '0' && **str <= '9')
	{
		*value *= 10;
		*value += **str - '0';
		(*str)++;
		// TODO: Handle overflow
	}
	return (true);
}

static bool parse_float_fractional(double *value, char **str)
{
	double decimal_place;

	if (**str != '.')
		return (true);
	(*str)++;
	if (**str < '0' || **str > '9')
		return (false);
	decimal_place = 0.1;
	while (**str >= '0' && **str <= '9')
	{
		*value += (**str - '0') * decimal_place;
		decimal_place *= 0.1;
		(*str)++;
		// TODO: Handle overflow OR 
	}
	return (true);
}

bool parse_float(double *value, char *str)
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

bool parse_vec3(t_vec3 *vec, char *str)
{
	char **components;

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

static bool parse_color_channel(double *value, char *str)
{
	int result;

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

bool parse_color(t_vec3 *color, char *str)
{
	char **channels;

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

bool parse_string(char **dest, char *str)
{
	if (!str)
		return (false);
	while (*str)
	{
		if (ft_isalpha(*str) == false)
			return (false);
		str++;
	}
	*dest = str;
	return (true);
}
