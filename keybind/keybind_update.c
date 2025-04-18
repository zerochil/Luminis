/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybind_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:12:05 by inajah            #+#    #+#             */
/*   Updated: 2025/04/18 08:01:47 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <keybind.h>

void	update_radius(t_keybind *keybind, t_entity *selected)
{
	t_object	*object;

	if (keybind == NULL || selected == NULL)
		return ;
	if (selected->type != OBJECT)
		return ;
	object = selected->object;
	object->radius += keybind->dir_flag * RADIUS_STEP;
	if (object->radius < 0)
		object->radius = 0;
}

void	update_height(t_keybind *keybind, t_entity *selected)
{
	t_object	*object;

	if (keybind == NULL || selected == NULL)
		return ;
	if (selected->type != OBJECT
		|| (selected->object->type != CYLINDER
			&& selected->object->type != CONE))
		return ;
	object = selected->object;
	object->height += keybind->dir_flag * HEIGHT_STEP;
	if (object->height < 0)
		object->height = 0;
}

void	update_angle(t_keybind *keybind, t_entity *selected)
{
	t_object	*object;

	if (keybind == NULL || selected == NULL)
		return ;
	if (selected->type != OBJECT || selected->object->type != CONE)
		return ;
	object = selected->object;
	object->angle += keybind->dir_flag * ANGLE_STEP;
	if (object->angle < 0)
		object->angle = 0;
	if (object->angle > 180)
		object->angle = 180;
}

void	update_pos(t_keybind *keybind, t_entity *selected)
{
	t_vec3	*pos;

	if (selected == NULL)
		return ;
	if (selected->type == CAMERA)
	{
		camera_translate(selected->camera, keybind->property, keybind->dir_flag
			* POS_STEP);
		return ;
	}
	if (selected->type == LIGHT)
		pos = &selected->light->origin;
	else if (selected->type == OBJECT)
		pos = &selected->object->origin;
	else
		return ;
	pos->x += keybind->dir_flag * (keybind->property == X_POS) * POS_STEP;
	pos->y += keybind->dir_flag * (keybind->property == Y_POS) * POS_STEP;
	pos->z += keybind->dir_flag * (keybind->property == Z_POS) * -POS_STEP;
}

void	update_rot(t_keybind *keybind, t_entity *selected)
{
	t_camera	*camera;
	t_object	*object;
	t_vec3		axis;
	double		angle;

	angle = keybind->dir_flag * ANGLE_STEP;
	if (selected->type == LIGHT)
		return ;
	if (selected->type == CAMERA)
	{
		camera = selected->camera;
		axis = get_rot_axis(keybind->property, camera->right, camera->up,
				camera->forward);
		camera_rotate(selected->camera, axis, angle);
	}
	else if (selected->object->type != SPHERE)
	{
		axis = get_rot_axis(keybind->property, (t_vec3){1, 0, 0}, (t_vec3){0, 1,
				0}, (t_vec3){0, 0, 1});
		object = selected->object;
		rotate(&object->orientation, axis, angle);
		object->orientation = vec3_normalize(object->orientation);
	}
}
