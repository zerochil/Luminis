/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybind_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:14:50 by inajah            #+#    #+#             */
/*   Updated: 2025/04/15 16:33:13 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <keybind.h>

t_vec3	get_rot_axis(int axis, t_vec3 a1, t_vec3 a2, t_vec3 a3)
{
	if (axis == X_ROT)
		return (a1);
	else if (axis == Y_ROT)
		return (a2);
	else
		return (a3);
}

void	update_fov(t_keybind *keybind, t_entity *selected)
{
	t_camera	*camera;

	if (selected->type != CAMERA)
		return ;
	camera = selected->camera;
	camera->fov += keybind->dir_flag * FOV_STEP;
	camera->scale = tan((camera->fov * M_PI / 179.0) / 2.0);
	keybind->dir_flag = 0;
}
