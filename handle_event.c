#include <handle_event.h>


t_hit find_intersection(t_scene *scene, t_ray *ray)
{
	t_hit closest_hit;
	t_object *object;
	t_array *objects;
	t_hit hit;
	size_t i;

	objects = scene->objects;
	hit.object = NULL;
	hit.distance = INFINITY;
	i = 0;
	while (i < objects->size)
	{
		object = array_get(objects, i);
		if (object->intersect(object, ray, &closest_hit))
		{
			if (closest_hit.distance < hit.distance)
				hit = closest_hit;
		}
		i++;
	}
	return (hit);
}

int keybind_cmp(void *keybind_ptr, void *keycode_ptr)
{
	t_keybind	*keybind;
	int			*keycode;

	keybind = keybind_ptr;
	keycode = keycode_ptr;
	return (*keycode == keybind->pos_key
		|| *keycode == keybind->neg_key);
}

t_object *get_selected_object(t_scene *scene, int x, int y)
{
	double aspect_ratio = (double)WIDTH / HEIGHT;
	double scale = tan((scene->camera.fov * M_PI / 180.0) / 2.0);
	t_matrix view_matrix = camera_matrix(scene->camera);
	double x_ndc = (x + 0.5) / WIDTH;
	double y_ndc = (y + 0.5) / HEIGHT;
	double x_screen = (2 * x_ndc - 1) * aspect_ratio * scale;
	double y_screen = (1 - 2 * y_ndc) * scale;
	t_vec3 camera_ray = vec3_mul_matrix((t_vec3){x_screen, y_screen, -1}, view_matrix);
	t_ray ray = {scene->camera.origin, vec3_normalize(camera_ray)};
	t_hit hit = find_intersection(scene, &ray);
	return (hit.object);
}

t_entity select_entity(t_scene *scene, int type, int mousex, int mousey)
{
	t_entity entity;

	entity.type = type;
	if (type == CAMERA)
		entity.camera = &scene->camera;
	if (type == LIGHT)
		entity.light = scene->lights->data[0];
	if (type == OBJECT)
	{
		entity.object = get_selected_object(scene, mousex, mousey);
		if (entity.object == NULL)
			entity.type = NONE;
	}
	return (entity);
}

void	print_object(t_object *obj)
{
	char *type;
	switch (obj->type)
	{
	case SPHERE:
		type = "sp";
		break;
	case PLANE:
		type = "pl";
		break;
	case CYLINDER:
		type = "cy";
		break;
	case CONE:
		type = "co";
		break;
	default:
		type = "";
	}
	printf("%s %.2f,%.2f,%.2f %.2f 200,200,200 %s\n",
	type, obj->origin.x, obj->origin.y, obj->origin.z, obj->radius * 2, obj->texture_name);
}
int	on_key_press(int keycode, t_scene *scene)
{
	t_keybind	*keybind;

	if (keycode == KEY_ESC)
		close_win(&scene->mlx);
	if (keycode == ' ')
		scene->mlx.control.selected = select_entity(scene, CAMERA, 0, 0);
	if (keycode == 'l')
		scene->mlx.control.selected = select_entity(scene, LIGHT, 0, 0);
	if (keycode == 'p')
		array_do(scene->objects, (void *)print_object);
	else
	{
		keybind = array_find(scene->mlx.control.keybinds, &keycode, keybind_cmp);
		if (keybind != NULL)
			keybind_set_dir_flag(keybind, keycode);
	}
	return (0);
}

int	on_key_release(int keycode, t_scene *scene)
{
	t_keybind	*keybind;
	t_mlx		*mlx;

	mlx = &scene->mlx;
	keybind = array_find(mlx->control.keybinds, &keycode, keybind_cmp);
	if (keybind != NULL)
		keybind_reset_dir_flag(keybind, keycode);
	return (0);
}

int	on_mouse_event(int keycode, int x, int y, t_scene *scene)
{
	t_keybind	*keybind;
	t_mlx		*mlx;

	mlx = &scene->mlx;
	if (keycode == KEY_LEFT_CLICK)
	{
		mlx->control.selected = select_entity(scene, OBJECT, x, y);
		return (1);
	}
	keybind = array_find(mlx->control.keybinds, &keycode, keybind_cmp);
	if (keybind != NULL)
		keybind_set_dir_flag(keybind, keycode);
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
