#include <minirt.h>


t_control	control_init(t_scene *scene)
{
	t_control control;

	control.selected.type = OBJECT;
	control.selected.camera = NULL;
	control.selected.light = NULL;
	control.selected.object = scene->objects->data[0];
	control.keybinds = keybinds_init();
	return (control);
}


void window_init(t_scene *scene)
{
	// TODO: check failure of both
	scene->mlx.ptr = mlx_init();
	scene->mlx.win = mlx_new_window(scene->mlx.ptr, WIDTH, HEIGHT, "Luminis");
}

int texture_cmp(t_texture *texture, char *name)
{
	return (ft_strcmp(texture->name, name) == 0);
}

bool post_parse(t_scene *scene)
{
	size_t i;
	t_texture *texture;

	i = 0;
	while (i < scene->objects->size)
	{
		t_object *object = array_get(scene->objects, i);
		if (object->texture_name == NULL)
			object->texture = create_texture("default", TEXTURE_SOLID, evaluate_solid_texture);
		else
		{
			texture = array_find(scene->textures, object->texture_name, (void *)texture_cmp);
			if (texture == NULL)
				return (parser_error("Texture not found"));
			object->texture = texture;
		}
		i++;
	}
	return (true);
}

int main(int argc, char **argv)
{
	t_scene scene;

	scene = (t_scene){0};
	window_init(&scene);

	/*char *path;*/
	/*t_texture texture;*/
	/*path = "textures/world_map.xpm";*/
	/*texture.type = TEXTURE_COLORED_MAP;*/
	/*if (texture_load(scene.mlx.ptr, &texture, path) == false)*/
	/*	return (ft_putstr_fd("Error: Failed to load texture\n", 2), 1);*/


	// TODO: COLORED BUMP MAP
	// you should flatten texture struct
	// in said struct, you should have an entry image;
	// and if you were to handle colored_bump, you'll need another image entry (image2)
	//
	// TODO: checkerboard: cone UV calculations fails when the axis is aligned with world axis

	if (argc != 2)
		return (ft_putstr_fd("Error\nInvalid number of arguments\n", 2), 1);
	if (parse_scene(&scene, argv[1]) == false)
		return (1);
	if (post_parse(&scene) == false)
		return (1);

	scene.mlx.control = control_init(&scene);

	render_scene(&scene);
}
