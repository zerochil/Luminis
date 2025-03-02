#include <minirt.h>



int main(int argc, char **argv)
{
	t_scene		scene;

	if (argc != 2)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	if(parse_scene(&scene, argv[1]) == false)
		return (ft_putstr_fd("Error: Failed to parse scene\n", 2), 1);
	print_scene(&scene);

	render_scene(&scene);
}
