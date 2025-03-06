#include <handle_event.h>



int	on_key_event(int keycode, t_mlx *mlx)
{
	t_camera	*camera = &mlx->scene.camera;
	if (keycode == KEY_ESC)
		close_win(mlx);
	if (keycode == 'a')
		camera_translate(camera, RIGHT, -STEP);
	if (keycode == 'd')
		camera_translate(camera, RIGHT, STEP);
	if (keycode == 'w')
		camera_translate(camera, FORWARD, STEP);
	if (keycode == 's')
		camera_translate(camera, FORWARD, -STEP);
	if (keycode == 'q')
		camera_translate(camera, UP, STEP);
	if (keycode == 'e')
		camera_translate(camera, UP, -STEP);
	if (keycode == KEY_LEFT)
		camera_rotate(camera, vec3_rotateY, ANGLE);
	if (keycode == KEY_RIGHT)
		camera_rotate(camera, vec3_rotateY, -ANGLE);
	if (keycode == KEY_UP)
		camera_rotate(camera, vec3_rotateX, -ANGLE);
	if (keycode == KEY_DOWN)
		camera_rotate(camera, vec3_rotateX, ANGLE);
	return (0);
}

int	on_mouse_event(int keycode, int x, int y, t_mlx *mlx)
{
	t_camera	*camera = &mlx->scene.camera;

	(void)x;
	(void)y;
	if (keycode == KEY_SCROLL_UP)
		camera->fov = (camera->fov - 1 > 0) ? camera->fov - 1 : 0;
	if (keycode == KEY_SCROLL_DOWN)
		camera->fov = (camera->fov + 1 < 180) ? camera->fov + 1 : 180;
	return (1);
}

int	close_win(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->image.ptr);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}
