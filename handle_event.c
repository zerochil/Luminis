#include <handle_event.h>

int keybind_cmp(void *keybind_ptr, void *keycode_ptr)
{
	t_keybind	*keybind;
	int			*keycode;

	keybind = keybind_ptr;
	keycode = keycode_ptr;
	return (*keycode == keybind->pos_key
		|| *keycode == keybind->neg_key);
}

t_entity select_entity(t_scene *scene, int type)
{
	t_entity entity;

	entity.type = type;
	if (type == CAMERA)
		entity.camera = &scene->camera;
	if (type == LIGHT)
		entity.light = scene->lights->data[0];
	if (type == OBJECT)
		entity.object = scene->objects->data[0];
	return (entity);
}

int	on_key_press(int keycode, t_mlx *mlx)
{
	t_keybind	*keybind;

	if (keycode == KEY_ESC)
		close_win(mlx);
	if (keycode == ' ')
		mlx->control.selected = select_entity(&mlx->scene, CAMERA);
	if (keycode == 'l')
		mlx->control.selected = select_entity(&mlx->scene, LIGHT);
	else
	{
		keybind = array_find(mlx->control.keybinds, &keycode, keybind_cmp);
		if (keybind != NULL)
			keybind_set_dir_flag(keybind, keycode);
	}
	return (0);
}

int	on_key_release(int keycode, t_mlx *mlx)
{
	t_keybind	*keybind;

	keybind = array_find(mlx->control.keybinds, &keycode, keybind_cmp);
	if (keybind != NULL)
		keybind_reset_dir_flag(keybind, keycode);
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
