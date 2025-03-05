#include <minirt.h>



#include <texture.h>



void window_init(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "Luminis");
}

int main(int argc, char **argv)
{
	t_scene		scene;

	scene = (t_scene){0};
	if (argc != 2)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	if(parse_scene(&scene, argv[1]) == false)
		return (ft_putstr_fd("Error: Failed to parse scene\n", 2), 1);
	/*print_scene(&scene);*/

	t_mlx	mlx;

	mlx = (t_mlx){0};
	window_init(&mlx);
	mlx.scene = &scene;

	t_texture brick_wall;
	if (load_texture(mlx.ptr, "textures/bricks.xpm", &brick_wall) == false)
		return (ft_putstr_fd("Error: Failed to load texture\n", 2), 1);

	/*printf("brick_wall.width: %d\n", brick_wall.width);*/
	/*printf("brick_wall.height: %d\n", brick_wall.height);*/
	/*printf("brick_wall.ptr[0]: %f\n", brick_wall.ptr[0]);*/
	/*printf("brick_wall.ptr[1]: %f\n", brick_wall.ptr[1]);*/

	render_scene(&mlx);
}
