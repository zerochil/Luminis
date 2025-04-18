/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:57:44 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/15 16:57:45 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	destroy_mlx(t_scene *scene)
{
	if (scene->mlx.win != NULL)
	{
		mlx_destroy_window(scene->mlx.ptr, scene->mlx.win);
		scene->mlx.win = NULL;
	}
	if (scene->mlx.ptr != NULL)
	{
		mlx_destroy_display(scene->mlx.ptr);
		free(scene->mlx.ptr);
		scene->mlx.ptr = NULL;
	}
}

void	mlx_start(t_scene *scene)
{
	scene->mlx.ptr = mlx_init();
	if (scene->mlx.ptr == NULL)
	{
		ft_putstr_fd("Error\nFailed to initialize mlx\n", 2);
		exit(1);
	}
	resource_track(scene, (void *)destroy_mlx);
}

void	window_start(t_scene *scene)
{
	scene->mlx.win = mlx_new_window(scene->mlx.ptr, WIDTH, HEIGHT, "Luminis");
	if (scene->mlx.win == NULL)
	{
		ft_putstr_fd("Error\nFailed to create window\n", 2);
		manager_free_everything();
		exit(1);
	}
}
