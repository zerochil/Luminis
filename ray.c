/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:54:06 by inajah            #+#    #+#             */
/*   Updated: 2025/04/15 14:10:16 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	ray_from_screen(t_camera *cam, int screen_x, int screen_y)
{
	double x_scr;
	double y_scr;
	t_vec3 cam_ray;

	x_scr = (2 * ((screen_x + 0.5) / WIDTH) - 1) * cam->ratio * cam->scale;
	y_scr = (1 - 2 * ((screen_y + 0.5) / HEIGHT)) * cam->scale;
	cam_ray = vec3_mul_matrix((t_vec3){x_scr, y_scr, -1}, cam->view);
	return ((t_ray){cam->origin, vec3_normalize(cam_ray)});
}