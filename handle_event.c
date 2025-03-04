#include <handle_event.h>



int	on_key_event(int keycode, t_mlx *mlx)
{
	t_camera	*camera = &mlx->scene->camera;
	if (keycode == KEY_ESC)
		close_win(mlx);
	if (keycode == 'a')
		camera->origin.x += STEP;
	if (keycode == 'd')
		camera->origin.x -= STEP;
	if (keycode == 'w')
		camera->origin.y -= STEP;
	if (keycode == 's')
		camera->origin.y += STEP;
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
	t_camera	*camera = &mlx->scene->camera;
	double aspect_ratio = (double)WIDTH / HEIGHT;
	double scale = tan((camera->fov * M_PI / 180.0) / 2.0);
	x = WIDTH / 2;
	y = HEIGHT / 2;
	double x_ndc = (x + 0.5) / WIDTH;
	double y_ndc = (y + 0.5) / HEIGHT;
	double x_screen = (2 * x_ndc - 1) * aspect_ratio * scale;
	double y_screen = (1 - 2 * y_ndc) * scale;
	t_vec3		origin = camera->origin;
	t_matrix view_matrix = camera_matrix(*camera);
	t_vec3 direction = vec3_mul_matrix((t_vec3){x_screen, y_screen, -1}, view_matrix);
	//printf("%f, %f, %f\n", direction.x, direction.y, direction.z);

	if (keycode == KEY_SCROLL_UP)
		camera->origin = vec3_add(origin, vec3_mul_scalar(direction, -STEP));
	if (keycode == KEY_SCROLL_DOWN)
		camera->origin = vec3_add(origin, vec3_mul_scalar(direction, STEP));
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