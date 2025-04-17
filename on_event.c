/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:39:59 by inajah            #+#    #+#             */
/*   Updated: 2025/04/17 20:29:10 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <on_event.h>

int	on_key_press(int keycode, t_scene *scene)
{
	t_keybind	*keybind;

	if (keycode == KEY_ESC)
		close_win(scene);
	if (keycode == ' ')
		scene->mlx.control.selected = select_entity(scene, CAMERA, 0, 0);
	if (keycode == 'l')
		scene->mlx.control.selected = select_entity(scene, LIGHT, 0, 0);
	else
	{
		keybind = array_find(scene->mlx.control.keybinds, &keycode,
				keybind_cmp);
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
