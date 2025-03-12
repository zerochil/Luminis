#include <parser.h>

bool	parse_line_ambient(t_scene *scene, char **infos)
{
	if (ft_strarr_len(infos) != 3)
		return (parser_error("Ambient light must have 2 arguments"));
	if (scene->ambient.is_declared)
		return (parser_error("Ambient light already declared"));
	if (parse_float(&scene->ambient.intensity, infos[1]) == false)
		return (parser_error("Ambient light intensity must be a float"));
	if (parse_color(&scene->ambient.color, infos[2]) == false)
		return (parser_error("Ambient light color must be a color"));
	if (in_interval(scene->ambient.intensity, 0, 1) == false)
		return (parser_error("Ambient light intensity must be between 0 and 1"));
	scene->ambient.is_declared = true;
	return (true);
}

bool	parse_line_camera(t_scene *scene, char **infos)
{
	if (ft_strarr_len(infos) != 4)
		return (parser_error("Camera must have 3 arguments"));
	if (scene->camera.is_declared)
		return (parser_error("Camera already declared"));
	if (parse_vec3(&scene->camera.origin, infos[1]) == false)
		return (parser_error("Camera origin must be a vec3"));
	if (parse_vec3(&scene->camera.forward, infos[2]) == false)
		return (parser_error("Camera direction must be a vec3"));
	if (parse_float(&scene->camera.fov, infos[3]) == false)
		return (parser_error("Camera fov must be a float"));
	if (in_interval(scene->camera.fov, 0, 180) == false)
		return (parser_error("Camera fov must be between 0 and 180"));
	scene->camera.forward = vec3_normalize(scene->camera.forward);
	if (is_normalized(scene->camera.forward) == false)
		return (parser_error("Camera direction must be normalized"));
	if (vec3_compare(scene->camera.forward, (t_vec3){0, 0, 0}))
		scene->camera.forward = (t_vec3){0, 0, -1};
	scene->camera.right = vec3_cross(scene->camera.forward, (t_vec3){0,1,0});
	scene->camera.up = vec3_cross(scene->camera.right, scene->camera.forward);
	// create_orthonormal_basis(scene->camera.forward, &scene->camera.right, &scene->camera.up);
	scene->camera.is_declared = true;
	return (true);
}

bool	parse_line_light(t_scene *scene, char **infos)
{
	t_light	*light;

	if (ft_strarr_len(infos) != 4)
		return (parser_error("Light must have 3 arguments"));
	light = track_malloc(sizeof(t_light));
	if (parse_vec3(&light->origin, infos[1]) == false)
		return (parser_error("Light origin must be a vec3"));
	if (parse_float(&light->intensity, infos[2]) == false)
		return (parser_error("Light intensity must be a float"));
	if (parse_color(&light->color, infos[3]) == false)
		return (parser_error("Light color must be a color"));
	if (in_interval(light->intensity, 0, 1) == false)
		return (parser_error("Light intensity must be between 0 and 1"));
	array_push(scene->lights, light);
	return (true);
}

bool	parse_line_sphere(t_scene *scene, char **infos)
{
	t_object	*object;

	if (ft_strarr_len(infos) != 4)
		return (parser_error("Sphere must have 4 arguments"));
	object = object_create(SPHERE);
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (parser_error("Sphere origin must be a vec3"));
	if (parse_float(&object->radius, infos[2]) == false)
		return (parser_error("Sphere radius must be a float"));
	if (parse_color(&object->color, infos[3]) == false)
		return (parser_error("Sphere color must be a color"));
	if (in_interval(object->radius, 0, INFINITY) == false)
		return (parser_error("Sphere radius must be positive"));
	if (infos[4] && parse_string(&object->texture_name, infos[4]) == false)
		return (parser_error("Texture name must be composed of only characters"));
	object->radius /= 2;
	array_push(scene->objects, object);
	return (true);
}

bool	parse_line_plane(t_scene *scene, char **infos)
{
	t_object	*object;

	if (ft_strarr_len(infos) != 4)
		return (parser_error("Plane must have 3 arguments"));
	object = object_create(PLANE);
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (parser_error("Plane origin must be a vec3"));
	if (parse_vec3(&object->orientation, infos[2]) == false)
		return (parser_error("Plane normal must be a vec3"));
	if (parse_color(&object->color, infos[3]) == false)
		return (parser_error("Plane color must be a color"));
	object->orientation = vec3_normalize(object->orientation);
	//if (is_normalized(object->orientation) == false)
		//return (parser_error("Plane normal must be normalized"));
	array_push(scene->objects, object);
	return (true);
}

bool	parse_line_cylinder(t_scene *scene, char **infos)
{
	t_object	*object;

	if (ft_strarr_len(infos) != 6)
		return (parser_error("Cylinder must have 5 arguments"));
	object = object_create(CYLINDER);
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (parser_error("Cylinder origin must be a vec3"));
	if (parse_vec3(&object->orientation, infos[2]) == false)
		return (parser_error("Cylinder orientation must be a vec3"));
	if (parse_float(&object->radius, infos[3]) == false)
		return (parser_error("Cylinder radius must be a float"));
	if (parse_float(&object->height, infos[4]) == false)
		return (parser_error("Cylinder height must be a float"));
	if (parse_color(&object->color, infos[5]) == false)
		return (parser_error("Cylinder color must be a color"));
	if (in_interval(object->radius, 0, INFINITY) == false)
		return (parser_error("Cylinder radius must be positive"));
	if (in_interval(object->height, 0, INFINITY) == false)
		return (parser_error("Cylinder height must be positive"));
	object->orientation = vec3_normalize(object->orientation);
	if (is_normalized(object->orientation) == false)
		return (parser_error("Cylinder orientation must be normalized"));
	object->radius /= 2;
	array_push(scene->objects, object);
	return (true);
}

bool	parse_line_cone(t_scene *scene, char **infos)
{
	t_object	*object;

	if (ft_strarr_len(infos) != 5)
		return (parser_error("Cone must have 4 arguments"));
	object = object_create(CONE);
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (parser_error("Cone origin must be a vec3"));
	if (parse_vec3(&object->orientation, infos[2]) == false)
		return (parser_error("Cone orientation must be a vec3"));
	if (parse_float(&object->angle, infos[3]) == false)
		return (parser_error("Cone opening angle must be a float"));
	if (parse_color(&object->color, infos[4]) == false)
		return (parser_error("Cone color must be a color"));
	if (in_interval(object->angle, 0, 90) == false)
		return (parser_error("Cone opening angle must be in range [0, 90]"));
	object->orientation = vec3_normalize(object->orientation);
	if (is_normalized(object->orientation) == false)
		return (parser_error("Cone orientation must be normalized"));
	object->angle /= 2;
	array_push(scene->objects, object);
	return (true);
}

bool parse_texture_checker(t_texture *texture, char **infos)
{
	t_vec3 color1;
	t_vec3 color2;

	if (ft_strarr_len(infos) != 6)
		return (parser_error("Checker texture must have 4 arguments"));
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

bool parse_texture(t_scene *scene, char **infos)
{
	t_texture *texture;

	if (ft_strarr_len(infos) != 4)
		return (parser_error("Texture must have at least 3 arguments"));
	texture = track_malloc(sizeof(t_texture));
	if (parse_string(&texture->name, infos[1]) == false)
		return (parser_error("Texture name must be composed of only characters"));
	if (texture_set_type(texture, infos[2]) == false)
		return (parser_error("Unknown texture type (bump_map, checker)"));
	if (texture->type == TEXTURE_BUMP_MAP || texture->type == TEXTURE_COLORED_MAP)
		texture_load(scene->mlx.ptr, texture, infos[3]);
	else if (texture->type == TEXTURE_CHECKER && parse_texture_checker(texture, infos) == false)
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
	if (ft_strcmp(infos[0], "co") == 0)
		return (parse_line_cone(scene, infos));
	if (ft_strcmp(infos[0], "t") == 0)
		return (parse_texture(scene, infos));
	return (parser_error("Unknown identifier"));
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
		{
			free(line);
			return (false);
		}
		free(line);
	}
	return (true);
}
