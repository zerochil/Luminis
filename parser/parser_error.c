#include <parser.h>

bool parser_error(char *error)
{
	ft_putstr_fd("Error\n", 2);
	if (!error)
		return (false);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	return (false);
}
