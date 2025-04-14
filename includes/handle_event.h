/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:53:13 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 15:53:19 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_EVENT_H
# define HANDLE_EVENT_H

# include <camera.h>
# include <keybind.h>
# include <matrix.h>
# include <mlx.h>
# include <scene.h>
# include <vec3.h>

enum
{
	ON_KEY_PRESS = 2,
	ON_KEY_RELEASE = 3,
	ON_MOUSE_DOWN = 4,
	ON_MOUSE_UP = 5,
	ON_MOUSE_MOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

int	on_key_press(int keycode, t_scene *scene);
int	on_key_release(int keycode, t_scene *scene);
int	on_mouse_event(int keycode, int x, int y, t_scene *scene);
int	close_win(t_mlx *mlx);

#endif
