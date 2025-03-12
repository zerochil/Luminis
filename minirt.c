#include <minirt.h>
#include <texture.h>


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

	if (argc != 2)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	if (parse_scene(&scene, argv[1]) == false)
		return (ft_putstr_fd("Error: Failed to parse scene\n", 2), 1);
	if (post_parse(&scene) == false)
		return (ft_putstr_fd("Error: Failed to post parse scene\n", 2), 1);



	scene.mlx.control = control_init(&scene);

	//TODO: check if the scene has all the neccessary entities: light, camera
	// This is a temporary solution
	// The texture has to be inside the object
	// It should be loaded in object creation while parsing the scene

	/*t_vec3 color = color_new(mlx.scene.texture.ptr[0]);*/
	/*printf("brick_wall.ptr[0]: %f\n", mlx.scene.texture.ptr[0]);*/
	/*printf("brick_wall.ptr[1]: %f\n", mlx.scene.texture.ptr[1]);*/
	/*exit(0);*/

	render_scene(&scene);
}
