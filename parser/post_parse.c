/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:57:10 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/15 16:57:11 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int	texture_cmp(t_texture *texture, char *name)
{
	return (ft_strcmp(texture->name, name) == 0);
}

bool	check_textures(t_scene *scene)
{
	size_t		i;
	t_texture	*texture;
	t_object	*object;

	i = 0;
	while (i < scene->objects->size)
	{
		object = array_get(scene->objects, i);
		if (object->texture_name == NULL)
			object->texture = create_texture("default", TEXTURE_SOLID,
					evaluate_solid_texture);
		else
		{
			texture = array_find(scene->textures, object->texture_name,
					(void *)texture_cmp);
			if (texture == NULL)
				return (parser_error("Texture not found"));
			object->texture = texture;
		}
		i++;
	}
	return (true);
}

bool	post_parse(t_scene *scene)
{
	if (scene->camera.is_declared == false)
		return (parser_error("No camera found"));
	if (scene->ambient.is_declared == false)
		return (parser_error("No ambient light found"));
	if (scene->lights->size == 0)
		return (parser_error("No lights found"));
	if (scene->objects->size == 0)
		return (parser_error("No objects found"));
	if (check_textures(scene) == false)
		return (false);
	return (true);
}
