/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:51:17 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/15 09:32:28 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_control	control_init(t_scene *scene)
{
	t_control	control;

	control.selected = select_entity(scene, CAMERA, 0, 0);
	control.keybinds = keybinds_init();
	return (control);
}

void	window_init(t_scene *scene)
{
	scene->mlx.ptr = mlx_init();
	if (scene->mlx.ptr == NULL)
	{
		ft_putstr_fd("Error\nFailed to initialize mlx\n", 2);
		exit(1);
	}
	scene->mlx.win = mlx_new_window(scene->mlx.ptr, WIDTH, HEIGHT, "Luminis");
	if (scene->mlx.win == NULL)
	{
		mlx_destroy_display(scene->mlx.ptr);
		free(scene->mlx.ptr);
		ft_putstr_fd("Error\nFailed to create window\n", 2);
		exit(1);
	}
}

int	texture_cmp(t_texture *texture, char *name)
{
	return (ft_strcmp(texture->name, name) == 0);
}

bool	post_parse(t_scene *scene)
{
	size_t		i;
	t_texture	*texture;
	t_object	*object;

	i = 0;
	while (i < scene->objects->size)
	{
		object = array_get(scene->objects, i);
		if (object->texture_name == NULL)
			object->texture = create_texture("default", TEXTURE_SOLID,
					evaluate_solid_texture);
		else
		{
			texture = array_find(scene->textures, object->texture_name,
					(void *)texture_cmp);
			if (texture == NULL)
				return (parser_error("Texture not found"));
			object->texture = texture;
		}
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	scene = (t_scene){0};
	window_init(&scene);
	if (argc != 2)
		return (ft_putstr_fd("Error\nInvalid number of arguments\n", 2), 1);
	if (parse_scene(&scene, argv[1]) == false)
		return (1);
	if (post_parse(&scene) == false)
		return (1);
	scene.mlx.control = control_init(&scene);
	render_scene(&scene);
}
