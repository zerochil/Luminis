#include "minirt.h"

int main(int argc, char **argv)
{
	t_scene		scene;
	int			error;

	if (argc != 2)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	error = parse_scene(&scene, argv[1]);
}
