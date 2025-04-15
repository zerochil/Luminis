/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:53:13 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/15 17:32:37 by inajah           ###   ########.fr       */
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

t_control	control_init(t_scene *scene);
t_entity	select_entity(t_scene *scene, int type, int mousex, int mousey);

int			on_key_press(int keycode, t_scene *scene);
int			on_key_release(int keycode, t_scene *scene);
int			on_mouse_event(int keycode, int x, int y, t_scene *scene);
int			close_win(t_mlx *mlx);

#endif
