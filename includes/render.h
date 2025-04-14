/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:53:13 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 18:06:03 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <camera.h>
# include <handle_event.h>
# include <lighting.h>
# include <mlx.h>
# include <scene.h>

typedef struct s_raytrace_data
{
	double		ratio;
	double		scale;
	t_matrix	view;
	double		x_ndc;
	double		y_ndc;
	double		x_scr;
	double		y_scr;
	t_vec3		cam_ray;
	t_ray		ray;
	t_hit		hit;
} t_raytrace_data;

void	render_scene(t_scene *scene);

#endif
