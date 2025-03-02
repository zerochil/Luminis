#include <render.h>

void window_init(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, 480, 360, "Luminis");
}

int	close_win(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->image.ptr);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 65307) // waz that??
		close_win(mlx);
	return (0);
}

void raytrace(t_scene *scene, t_image *image)
{
	(void)scene;
	(void)image;
}

void	render_image(t_mlx *mlx, t_scene *scene)
{
	mlx->image.ptr = mlx_new_image(mlx->ptr, 480, 360);
	mlx->image.addr = mlx_get_data_addr(mlx->image.ptr, &mlx->image.bpp, &mlx->image.line_len, &mlx->image.endian);
	raytrace(scene, &mlx->image);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->image.ptr, 0, 0);
}

void	render_scene(t_scene *scene)
{
	t_mlx		mlx;

	window_init(&mlx);
	mlx_loop(mlx.ptr);
	mlx_hook(mlx.win, 17, 0, close_win, &mlx);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	render_image(&mlx, scene);
	mlx_loop(mlx.ptr);
	close_win(&mlx);
}
