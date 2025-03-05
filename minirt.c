#include <minirt.h>



#include <texture.h>



void window_init(t_mlx *mlx)
{
	// TODO: check failure of both
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "Luminis");
}

int main(int argc, char **argv)
{
	t_mlx	mlx;
	mlx = (t_mlx){0};

	if (argc != 2)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	if(parse_scene(&mlx.scene, argv[1]) == false)
		return (ft_putstr_fd("Error: Failed to parse scene\n", 2), 1);

	window_init(&mlx);

	// This is a temporary solution
	// The texture has to be inside the object
	// It should be loaded in object creation while parsing the scene
	if (load_texture(mlx.ptr, "textures/world.xpm", &mlx.scene.texture, IS_COLOR_TEXTURE) == false)
		return (ft_putstr_fd("Error: Failed to load texture\n", 2), 1);

	/*t_color color = color_new(mlx.scene.texture.ptr[0]);*/
	/*printf("brick_wall.ptr[0]: %f\n", mlx.scene.texture.ptr[0]);*/
	/*printf("brick_wall.ptr[1]: %f\n", mlx.scene.texture.ptr[1]);*/
	/*exit(0);*/

	render_scene(&mlx);
}
