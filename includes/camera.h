/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:53:13 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 15:53:22 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <matrix.h>
# include <scene.h>
# include <vec3.h>

enum
{
	FORWARD,
	UP,
	RIGHT,
};

t_matrix	camera_matrix(t_camera camera);
void		camera_rotate(t_camera *camera, t_vec3 axis, double angle);
void		camera_translate(t_camera *camera, int direction, double step);

#endif
