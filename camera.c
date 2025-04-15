/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:48:38 by inajah            #+#    #+#             */
/*   Updated: 2025/04/15 13:58:03 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <camera.h>

static void	camera_update_view(t_camera *camera)
{
	camera->view.data[0] = camera->right.x;
	camera->view.data[1] = camera->right.y;
	camera->view.data[2] = camera->right.z;
	camera->view.data[3] = -vec3_dot(camera->right, camera->origin);
	camera->view.data[4] = camera->up.x;
	camera->view.data[5] = camera->up.y;
	camera->view.data[6] = camera->up.z;
	camera->view.data[7] = -vec3_dot(camera->up, camera->origin);
	camera->view.data[8] = -camera->forward.x;
	camera->view.data[9] = -camera->forward.y;
	camera->view.data[10] = -camera->forward.z;
	camera->view.data[11] = vec3_dot(camera->forward, camera->origin);
	camera->view.data[12] = 0.0f;
	camera->view.data[13] = 0.0f;
	camera->view.data[14] = 0.0f;
	camera->view.data[15] = 1.0f;
}

void	camera_init(t_camera *camera)
{
	camera->ratio = (double)WIDTH / HEIGHT;
	camera->scale = tan((camera->fov * M_PI / 180.0) / 2.0);
	camera_update_view(camera);
}

void	camera_rotate(t_camera *camera, t_vec3 axis, double angle)
{
	rotate_dev(&camera->forward, axis, angle);
	rotate_dev(&camera->up, axis, angle);
	camera->right = vec3_normalize(vec3_cross(camera->forward, camera->up));
	camera_update_view(camera);
}

void	camera_translate(t_camera *camera, int direction, double step)
{
	t_vec3	dir;

	if (direction == Z_POS)
		dir = camera->forward;
	else if (direction == Y_POS)
		dir = camera->up;
	else
		dir = camera->right;
	camera->origin = vec3_add(camera->origin, vec3_mul_scalar(dir, step));
	camera_update_view(camera);
}
