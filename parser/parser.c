/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:48:30 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 15:00:26 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	parse_line_ambient(t_scene *scene, char **infos);
bool	parse_line_camera(t_scene *scene, char **infos);
bool	parse_line_light(t_scene *scene, char **infos);
bool	parse_line_sphere(t_scene *scene, char **infos);
bool	parse_line_plane(t_scene *scene, char **infos);
bool	parse_line_cylinder(t_scene *scene, char **infos);
bool	parse_line_cone(t_scene *scene, char **infos);

bool	parse_texture_checker(t_texture *texture, char **infos)
{
	t_vec3	color1;
	t_vec3	color2;

	if (ft_strarr_len(infos) != 6)
		return (parser_error("Checker texture must have 5 arguments"));
	if (parse_float(&texture->checker.scale, infos[3]) == false)
		return (parser_error("Checker scale must be a float"));
	if (parse_color(&color1, infos[4]) == false)
		return (parser_error("Checker color1 must be a color"));
	if (parse_color(&color2, infos[5]) == false)
		return (parser_error("Checker color2 must be a color"));
	texture->checker.color1 = color1;
	texture->checker.color2 = color2;
	return (true);
}

bool	parse_texture(t_scene *scene, char **infos)
{
	t_texture	*texture;

	if (ft_strarr_len(infos) < 4 || ft_strarr_len(infos) > 6)
		return (parser_error("Texture must have 3 to 5 arguments"));
	texture = track_malloc(sizeof(t_texture));
	if (parse_string(&texture->name, infos[1]) == false)
		return (parser_error("Texture name isn't composed of only characters"));
	if (texture_set_type(texture, infos[2]) == false)
		return (parser_error("allowed textures: (bump_map, colored, checker)"));
	if (texture->type == TEXTURE_BUMP_MAP
		|| texture->type == TEXTURE_COLORED_MAP)
		texture_load(scene->mlx.ptr, texture, infos[3]);
	else if (texture->type == TEXTURE_CHECKER
		&& parse_texture_checker(texture, infos) == false)
		return (false);
	array_push(scene->textures, texture);
	return (true);
}

bool	parse_line(t_scene *scene, char *line)
{
	char	**infos;

	infos = ft_split(line, ' ');
	resource_track(infos, free_strings);
	if (!infos || !infos[0] || *infos[0] == '#')
		return (true);
	if (ft_strcmp(infos[0], "A") == 0)
		return (parse_line_ambient(scene, infos));
	if (ft_strcmp(infos[0], "C") == 0)
		return (parse_line_camera(scene, infos));
	if (ft_strcmp(infos[0], "L") == 0)
		return (parse_line_light(scene, infos));
	if (ft_strcmp(infos[0], "sp") == 0)
		return (parse_line_sphere(scene, infos));
	if (ft_strcmp(infos[0], "pl") == 0)
		return (parse_line_plane(scene, infos));
	if (ft_strcmp(infos[0], "cy") == 0)
		return (parse_line_cylinder(scene, infos));
	if (ft_strcmp(infos[0], "co") == 0)
		return (parse_line_cone(scene, infos));
	if (ft_strcmp(infos[0], "t") == 0)
		return (parse_texture(scene, infos));
	return (parser_error("Unknown identifier"));
}

void	trim_newline(char *line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return ;
		}
		i++;
	}
}

bool	parse_scene(t_scene *scene, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (parser_error("Failed to open file"));
	scene->lights = array_create();
	scene->objects = array_create();
	scene->textures = array_create();
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		trim_newline(line);
		if (parse_line(scene, line) == false)
			return (free(line), false);
		free(line);
	}
	close(fd);
	if (post_parse(scene) == false)
		return (false);
	return (true);
}
