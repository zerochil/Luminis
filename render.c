#include <render.h>


void raytrace(t_scene *scene)
{
	double aspect_ratio = (double)WIDTH / HEIGHT;
	double scale = tan((scene->camera.fov * M_PI / 180.0) / 2.0);
	t_matrix view_matrix = camera_matrix(scene->camera);

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			double x_ndc = (x + 0.5) / WIDTH;
			double y_ndc = (y + 0.5) / HEIGHT;
			double x_screen = (2 * x_ndc - 1) * aspect_ratio * scale;
			double y_screen = (1 - 2 * y_ndc) * scale;
			t_vec3 camera_ray = vec3_mul_matrix((t_vec3){x_screen, y_screen, -1}, view_matrix);
			t_ray ray = {scene->camera.origin, vec3_normalize(camera_ray)};
			t_hit hit = find_intersection(scene, &ray);
			(void)scene;
			if (hit.object)
				put_pixel(&scene->mlx.image, x, y, calculate_lighting(scene, &hit));
			else
				put_pixel(&scene->mlx.image, x, y, (t_vec3){18, 18, 18});
		}
	}
}

bool	apply_transformation(t_control control)
{
	t_keybind	*keybind;
	bool		state_changed;
	size_t i;

	if (control.selected.type == NONE)
		return (false);
	i = 0;
	state_changed = false;
	while (i < control.keybinds->size)
	{
		keybind = array_get(control.keybinds, i);
		if (keybind->dir_flag != 0)
		{
			keybind->update(keybind, &control.selected);
			state_changed = true;
		} 
		i++;
	}
	return (state_changed);
}

int	render_image(t_scene *scene)
{
	static bool first = true;

	if (apply_transformation(scene->mlx.control) || first)
	{
		raytrace(scene);
		first = false;
	}
	mlx_put_image_to_window(scene->mlx.ptr, scene->mlx.win, scene->mlx.image.ptr, 0, 0);
	return (1);
}

void	render_scene(t_scene	*scene)
{
	new_image(scene->mlx.ptr, &scene->mlx.image, WIDTH, HEIGHT);
	mlx_hook(scene->mlx.win, ON_DESTROY, 0, close_win, &scene->mlx);
	mlx_hook(scene->mlx.win, ON_KEY_PRESS, 1L << 0, on_key_press, scene);
	mlx_hook(scene->mlx.win, ON_KEY_RELEASE, 1L << 1, on_key_release, scene);
	mlx_mouse_hook(scene->mlx.win, on_mouse_event, scene);
	mlx_loop_hook(scene->mlx.ptr, render_image, scene);
	mlx_loop(scene->mlx.ptr);
	close_win(&scene->mlx);
}
