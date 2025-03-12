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
	scene->mlx.control = control_init(scene);
}

int main(int argc, char **argv)
{
	t_scene scene;

	scene = (t_scene){0};
	if (argc != 2)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	if (parse_scene(&scene, argv[1]) == false)
		return (ft_putstr_fd("Error: Failed to parse scene\n", 2), 1);

	//TODO: check if the scene has all the neccessary entities: light, camera
	window_init(&scene);
	// This is a temporary solution
	// The texture has to be inside the object
	// It should be loaded in object creation while parsing the scene
	/*char *path;*/
	/*path = "textures/world_map.xpm";*/
	//path = "textures/brick_wall.xpm";
	/*if (load_texture(scmlx.ptr, path, &mlx.scene.texture, IS_COLOR_TEXTURE) == false)*/
	/*	return (ft_putstr_fd("Error: Failed to load texture\n", 2), 1);*/

	/*t_vec3 color = color_new(mlx.scene.texture.ptr[0]);*/
	/*printf("brick_wall.ptr[0]: %f\n", mlx.scene.texture.ptr[0]);*/
	/*printf("brick_wall.ptr[1]: %f\n", mlx.scene.texture.ptr[1]);*/
	/*exit(0);*/

	render_scene(&scene);
}
