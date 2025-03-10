#include "parser.h"

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


void basis_from_forward(t_vec3 *forward, t_vec3 *right, t_vec3 *up)
{
	if (float_eq(fabs(forward->y), 1.0))
		*up = (t_vec3){0, 0, -1};
	else
		*up = (t_vec3){0, 1, 0};

	*right = vec3_cross(*forward, *up);
	*right = vec3_normalize(*right);
	*up = vec3_cross(*right, *forward);
	*up = vec3_normalize(*up);
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
	create_orthonormal_basis(scene->camera.forward, &scene->camera.right, &scene->camera.up);
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
		return (parser_error("Sphere must have 3 arguments"));
	object = object_create(SPHERE);
	if (parse_vec3(&object->origin, infos[1]) == false)
		return (parser_error("Sphere origin must be a vec3"));
	if (parse_float(&object->sphere.radius, infos[2]) == false)
		return (parser_error("Sphere radius must be a float"));
	if (parse_color(&object->color, infos[3]) == false)
		return (parser_error("Sphere color must be a color"));
	if (in_interval(object->sphere.radius, 0, INFINITY) == false)
		return (parser_error("Sphere radius must be positive"));
	object->sphere.radius /= 2;
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
	if (parse_vec3(&object->plane.normal, infos[2]) == false)
		return (parser_error("Plane normal must be a vec3"));
	if (parse_color(&object->color, infos[3]) == false)
		return (parser_error("Plane color must be a color"));
	object->plane.normal = vec3_normalize(object->plane.normal);
	//if (is_normalized(object->plane.normal) == false)
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
	if (parse_vec3(&object->cylinder.orientation, infos[2]) == false)
		return (parser_error("Cylinder orientation must be a vec3"));
	if (parse_float(&object->cylinder.radius, infos[3]) == false)
		return (parser_error("Cylinder radius must be a float"));
	if (parse_float(&object->cylinder.height, infos[4]) == false)
		return (parser_error("Cylinder height must be a float"));
	if (parse_color(&object->color, infos[5]) == false)
		return (parser_error("Cylinder color must be a color"));
	if (in_interval(object->cylinder.radius, 0, INFINITY) == false)
		return (parser_error("Cylinder radius must be positive"));
	if (in_interval(object->cylinder.height, 0, INFINITY) == false)
		return (parser_error("Cylinder height must be positive"));
	object->cylinder.orientation = vec3_normalize(object->cylinder.orientation);
	if (is_normalized(object->cylinder.orientation) == false)
		return (parser_error("Cylinder orientation must be normalized"));
	object->cylinder.radius /= 2;
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
	if (parse_vec3(&object->cone.orientation, infos[2]) == false)
		return (parser_error("Cone orientation must be a vec3"));
	if (parse_float(&object->cone.angle, infos[3]) == false)
		return (parser_error("Cone opening angle must be a float"));
	if (parse_color(&object->color, infos[4]) == false)
		return (parser_error("Cone color must be a color"));
	if (in_interval(object->cone.angle, 0, 90) == false)
		return (parser_error("Cone opening angle must be in range [0, 90]"));
	object->cone.orientation = vec3_normalize(object->cone.orientation);
	if (is_normalized(object->cone.orientation) == false)
		return (parser_error("Cone orientation must be normalized"));
	object->cone.angle /= 2;
	array_push(scene->objects, object);
	return (true);
}

bool parse_material(t_scene *scene, char **infos)
{
	t_material *material;

	if (ft_strarr_len(infos) != 6)
		return (parser_error("Material must have 5 arguments"));
	material = track_malloc(sizeof(t_material));
	if (parse_string(&material->name, infos[1]) == false)
		return (parser_error("Material name must be composed of only characters"));
	if (parse_color(&material->albedo, infos[2]) == false)
		return (parser_error("Material albedo must be a color"));
	if (parse_float(&material->roughness, infos[3]) == false)
		return (parser_error("Material roughness must be a float"));
	if (parse_float(&material->ior, infos[4]) == false)
		return (parser_error("Material ior must be a float"));
	if (parse_float(&material->metallic, infos[5]) == false)
		return (parser_error("Material metallic must be a float"));
	if (in_interval(material->roughness, 0, 1) == false)
		return (parser_error("Material roughness must be between 0 and 1"));
	if (in_interval(material->ior, 0, INFINITY) == false)
		return (parser_error("Material ior must be positive"));
	if (in_interval(material->metallic, 0, 1) == false)
		return (parser_error("Material metallic must be between 0 and 1"));
	array_push(scene->materials, material);
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
	if (ft_strcmp(infos[0], "m") == 0)
		return (parse_material(scene, infos));
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
	scene->materials = array_create();
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
