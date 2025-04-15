/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_event_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:39:44 by inajah            #+#    #+#             */
/*   Updated: 2025/04/15 17:52:05 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <on_event.h>

t_control	control_init(t_scene *scene)
{
	t_control	control;

	control.selected = select_entity(scene, CAMERA, 0, 0);
	control.keybinds = keybinds_init();
	return (control);
}

static t_object	*select_object(t_scene *scene, int x, int y)
{
	t_ray	ray;
	t_hit	hit;

	ray = ray_from_screen(&scene->camera, x, y);
	hit = find_intersection(scene, &ray);
	return (hit.object);
}

static t_light	*select_light(t_scene *scene)
{
	static int	light_index = 0;
	t_light		*light;

	if (light_index + 1 == (int)scene->lights->size)
		light_index = 0;
	else
		light_index++;
	light = array_get(scene->lights, light_index);
	return (light);
}

t_entity	select_entity(t_scene *scene, int type, int mousex, int mousey)
{
	t_entity	entity;

	entity.type = type;
	if (type == CAMERA)
		entity.camera = &scene->camera;
	else if (type == LIGHT)
		entity.light = select_light(scene);
	else if (type == OBJECT)
		entity.object = select_object(scene, mousex, mousey);
	if (entity.ptr == NULL)
		entity.type = NONE;
	return (entity);
}

int	close_win(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->image.ptr);
	manager_free_everything();
	exit(0);
}
