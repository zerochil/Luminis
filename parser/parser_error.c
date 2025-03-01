#include <parser.h>

bool parser_error(char *error)
{
	if (!error)
		return (false);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	return (false);
}
