/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:53:13 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/18 09:38:06 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <entity.h>
# include <keybind.h>
# include <libft.h>
# include <libmath.h>
# include <mlx_image.h>

enum
{
	WIDTH = 1280,
	HEIGHT = 720,
	ASPECT_RATIO = WIDTH / HEIGHT,
};

typedef struct s_control
{
	t_entity	selected;
	t_array		*keybinds;
}				t_control;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	t_image		image;
	t_control	control;
}				t_mlx;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_array			*lights;
	t_array			*objects;
	t_array			*materials;
	t_array			*textures;
	t_thread_pool	pool;
	t_mlx			mlx;
}				t_scene;

#endif
