#include "parser.h"

bool	parse_line_ambient(t_scene *scene, char **infos)
{
	if (ft_strarr_len(infos) != 3)
		return (false);
	if (scene->ambient.is_declared)
		return (false);
	if (parse_float(&scene->ambient.intensity, infos[1]) == false)
		return (false);
	if (parse_color(&scene->ambient.color, infos[2]) == false)
		return (false);
	if (in_interval(scene->ambient.intensity, 0, 1) == false)
		return (false);
	scene->ambient.is_declared = true;
	return (true);
}

bool	parse_line_camera(t_scene *scene, char **infos)
{
	t_vec3	tmp;

	if (ft_strarr_len(infos) != 4)
		return (false);
	if (scene->camera.is_declared)
		return (false);
	if (parse_vec3(&scene->camera.origin, infos[1]) == false)
		return (false);
	if (parse_vec3(&tmp, infos[2]) == false)
		return (false);
	if (is_normalized(tmp) == false)
		return (false);
	scene->camera.right = (t_vec3){tmp.x, 0, 0};
	scene->camera.up = (t_vec3){0, tmp.y, 0};
	scene->camera.direction = (t_vec3){0, 0, tmp.z};
	if (parse_float(&scene->camera.fov, infos[3]) == false)
		return (false);
	if (in_interval(scene->camera.fov, 0, 180) == false)
		return (false);
	scene->camera.is_declared = true;
	return (true);
}

bool	parse_line_light(t_scene *scene, char **infos)
{
	t_light	*light;

	if (ft_strarr_len(infos) != 4)
		return (false);
	light = track_malloc(sizeof(t_light));
	if (parse_vec3(&light->origin, infos[1]) == false)
		return (false);
	if (parse_float(&light->intensity, infos[2]) == false)
		return (false);
	if (parse_color(&light->color, infos[3]) == false)
		return (false);
	if (in_interval(light->intensity, 0, 1) == false)
		return (false);
	array_push(scene->lights, light);
	return (true);
}

bool	parse_line_sphere(t_scene *scene, char **infos)
{
	t_object	*object;

	if (ft_strarr_len(infos) != 4)
		return (false);
	object = track_malloc(sizeof(t_object));
	object->type = SPHERE;
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (false);
	if (parse_float(&object->sphere.radius, infos[2]) == false)
		return (false);
	if (parse_color(&object->color, infos[3]) == false)
		return (false);
	if (in_interval(object->sphere.radius, 0, INFINITY) == false)
		return (false);
	object->sphere.radius /= 2;
	array_push(scene->objects, object);
	return (true);
}

bool	parse_line_plane(t_scene *scene, char **infos)
{
	t_object	*object;

	if (ft_strarr_len(infos) != 4)
		return (false);
	object = track_malloc(sizeof(t_object));
	object->type = PLANE;
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (false);
	if (parse_vec3(&object->plane.orientation, infos[2]) == false)
		return (false);
	if (parse_color(&object->color, infos[3]) == false)
		return (false);
	if (is_normalized(object->plane.orientation) == false)
		return (false);
	array_push(scene->objects, object);
	return (true);
}

bool	parse_line_cylinder(t_scene *scene, char **infos)
{
	t_object	*object;

	if (ft_strarr_len(infos) != 6)
		return (false);
	object = track_malloc(sizeof(t_object));
	object->type = CYLINDER;
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (false);
	if (parse_vec3(&object->cylinder.orientaiton, infos[2]) == false)
		return (false);
	if (parse_float(&object->cylinder.radius, infos[3]) == false)
		return (false);
	if (parse_float(&object->cylinder.height, infos[4]) == false)
		return (false);
	if (parse_color(&object->color, infos[5]) == false)
		return (false);
	if (in_interval(object->cylinder.radius, 0, INFINITY) == false)
		return (false);
	if (in_interval(object->cylinder.height, 0, INFINITY) == false)
		return (false);
	if (is_normalized(object->cylinder.orientaiton) == false)
		return (false);
	object->cylinder.radius /= 2;
	array_push(scene->objects, object);
	return (true);
}

bool	parse_line(t_scene *scene, char *line)
{
	char	**infos;

	infos = ft_split(line, ' ');
	resource_track(infos, free_strings);
	if (!infos || !infos[0])
		return (true); // TODO, Should it return true or false? WHY?
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
	return (false);
}

void trim_newline(char *line)
{
	int i;

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
		return (false);
	scene->lights = array_create();
	scene->objects = array_create();
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		trim_newline(line);
		if (parse_line(scene, line) == false)
		{
			free(line);
			return (false);
		}
		free(line);
	}
	return (true);
}
