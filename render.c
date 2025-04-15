/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:01:12 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/15 14:08:05 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include "ray.h"

void	raytrace(t_scene *scene)
{
	t_hit			hit;
	t_ray			ray;
	size_t			x;
	size_t			y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ray = ray_from_screen(&scene->camera, x, y);
			hit = find_intersection(scene, &ray);
			if (hit.object)
				put_pixel(&scene->mlx.image, x, y, calculate_lighting(scene,
						&hit));
			else
				put_pixel(&scene->mlx.image, x, y, (t_vec3){18, 18, 18});
		}
	}
}

bool	apply_transformation(t_control control)
{
	t_keybind	*keybind;
	bool		state_changed;
	size_t		i;

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
	static bool	first = true;

	if (apply_transformation(scene->mlx.control) || first)
	{
		raytrace(scene);
		first = false;
	}
	mlx_put_image_to_window(scene->mlx.ptr, scene->mlx.win,
		scene->mlx.image.ptr, 0, 0);
	return (1);
}

void	render_scene(t_scene *scene)
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
