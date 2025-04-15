/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:53:13 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/15 17:32:05 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <scene.h>
# include <camera.h>
# include <render.h>

t_ray	ray_from_screen(t_camera *scene, int screen_x, int screen_y);

#endif
