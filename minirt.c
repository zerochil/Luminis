/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:51:17 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/16 08:18:40 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	mlx_start(t_scene *scene);
void	window_start(t_scene *scene);

void	init(t_scene *scene)
{
	window_start(scene);
	scene->mlx.control = control_init(scene);
	camera_init(&scene->camera);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		return (ft_putstr_fd("Error\nInvalid number of arguments\n", 2), 1);
	scene = (t_scene){0};
	mlx_start(&scene);
	if (parse_scene(&scene, argv[1]) == false)
		return (manager_free_everything(), 1);
	init(&scene);
	render_scene(&scene);
	manager_free_everything();
}
