#include <render.h>

bool is_shadowed(t_scene *scene, t_ray ray, double light_distance)
{
	t_hit hit = find_intersection(scene, &ray);
	return (hit.object && hit.distance < light_distance);
}

void color_clamp(t_vec3 *color)
{
	color->x = fmin(fmax(color->x, 0.0), 1.0);
	color->y = fmin(fmax(color->y, 0.0), 1.0);
	color->z = fmin(fmax(color->z, 0.0), 1.0);
}



t_vec3 calculate_lighting(t_scene *scene, t_hit hit)
{
	t_vec3 total_light = {0.0, 0.0, 0.0};
	t_array *lights = scene->lights;
	t_light *light;

	t_vec3 color = hit.object->color;
	/*if (false && hit.object->type == SPHERE)*/
	/*{*/
		//t_uv uv = get_sphere_uv(hit);
		//color = color_new(get_texture_uv(&scene->texture, uv.u, uv.v));
	/*}*/

	/*if (false && hit.object->type == SPHERE)*/
	/*{*/
	/*	t_vec3 p = vec3_sub(hit.point, hit.object->origin);*/
	/*	double phi = acos(p.y/hit.object->radius);*/
	/*	double theta = atan2(p.z, p.x);*/
	/*	double scale = 20;*/
	/**/
	/*	double i = floor(phi / (M_PI / scale));*/
	/*	double j = floor(theta / ( 2 * M_PI / scale));*/
	/**/
	/*	if ((int)floor(i + j) % 2 == 0)*/
	/*		color = (t_vec3){255, 255, 255};*/
	/*	else*/
	/*		color = (t_vec3){0, 0, 0};*/
	/*}*/
	/**/
	/*if (false && hit.object->type == PLANE)*/
	/*{*/
	/*	double scale = 5;*/
	/**/
	/*	t_vec3 u;*/
	/*	t_vec3 v;*/
	/**/
	/*	create_orthonormal_basis(hit.normal, &u, &v);*/
	/*	double x = vec3_dot(hit.point, u);*/
	/*	double y = vec3_dot(hit.point, v);*/
	/**/
	/*	int s = (int)floor(x / scale);*/
	/*	int t = (int)floor(y / scale);*/
	/**/
	/*	if ((s + t) % 2 == 0)*/
	/*		color = (t_vec3){255, 255, 255};*/
	/*	else*/
	/*		color = (t_vec3){0, 0, 0};*/
	/*}*/

	/*if (false && hit.object->type == CYLINDER)*/
	/*{*/
		//t_uv uv = get_cylinder_uv(hit);
		
		//color = color_new(get_texture_uv(&scene->texture, uv.u, uv.v));
		// double scale = 10;
		// int s = floor(uv.u * scale);
		// int t = floor(uv.v * scale);
		// if ((s + t) % 2 == 0)
		// 	color = (t_vec3){255, 255, 255};
		// else
		// 	color = (t_vec3){0, 0, 0};
	/*}*/


	/*if (false && hit.object->type == SPHERE)*/
	/*{*/
	/*	t_uv uv = get_sphere_uv(hit);*/
	/**/
	/*	double coeff = .55;*/
	/**/
	/*	t_vec3 tangent;*/
	/*	t_vec3 bitangent;*/
	/**/
	/*	create_orthonormal_basis(hit.normal, &tangent, &bitangent);*/
	/**/
	/*	double tex_val = get_texture_uv(&scene->texture, uv.u, uv.v);*/
	/*	t_vec3 perturbed_normal = vec3_add(hit.normal, vec3_mul_scalar(bitangent, (fabs(tex_val)) * coeff));*/
	/*	//t_vec3 perturbed_normal = vec3_add(hit.normal, vec3_mul_scalar(vec3_add(tangent, bitangent), tex_val * coeff));*/
	/*	hit.normal = vec3_add(hit.normal, perturbed_normal);*/
	/*	hit.normal = vec3_normalize(hit.normal);*/
	/*}*/
	
	color = vec3_mul_scalar(color, 1.0/255.0);
	t_vec3 ambient = scene->ambient.color;
	ambient = vec3_mul_scalar(ambient, 1.0/255.0);
	ambient = vec3_mul_scalar(ambient, scene->ambient.intensity);
	ambient = vec3_mul(ambient, color);
	total_light = ambient;
	for (size_t i = 0; i < lights->size; i++)
	{
		light = array_get(lights, i);
		t_vec3 light_dir = vec3_normalize(vec3_sub(light->origin, hit.point));
		double light_dist = vec3_length(vec3_sub(light->origin, hit.point));
		if (is_shadowed(scene, (t_ray){vec3_add(hit.point, vec3_mul_scalar(hit.normal, EPSILON * 1000)), light_dir}, light_dist))
			continue;

		double diffuse_intensity = fmax(vec3_dot(hit.normal, light_dir), 0.0);
		if (diffuse_intensity > 0.0)
		{
			t_vec3 light_color = light->color;
			light_color = vec3_mul_scalar(light_color, 1.0/255.0);
			light_color = vec3_mul(light_color, color);
			double attenuation = 1.0 / (1.0 + 0.0001 * light_dist * light_dist);
			/*attenuation = 1;*/
			light_color = vec3_mul_scalar(light_color, light->intensity * attenuation);
			light_color = vec3_mul_scalar(light_color, diffuse_intensity * 1);
			total_light = vec3_add(total_light, light_color);

			
			t_vec3 reflect_dir = vec3_reflect(vec3_negate(light_dir), hit.normal);
			t_vec3 view_dir = vec3_normalize(vec3_sub(scene->camera.origin, hit.point));
			t_vec3 specular_color = {1.0, 1.0, 1.0}; // white because we don't have a specular color, only metallic objects have specular color
			specular_color = vec3_mul_scalar(specular_color, light->intensity * attenuation);
			specular_color = vec3_mul_scalar(specular_color, pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), 50.0));
			specular_color = vec3_mul_scalar(specular_color, 0.9);
			total_light = vec3_add(total_light, specular_color);

		}
	}
	/*color_mul(&color, &total_light);*/
	color = total_light;
	color_clamp(&color);
	return (vec3_mul_scalar(color, 255.0));
}

void raytrace(t_scene *scene, t_image *image)
{
	double aspect_ratio = (double)WIDTH / HEIGHT;
	double scale = tan((scene->camera.fov * M_PI / 180.0) / 2.0);
	t_matrix view_matrix = camera_matrix(scene->camera);

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			double x_ndc = (x + 0.5) / WIDTH;
			double y_ndc = (y + 0.5) / HEIGHT;
			double x_screen = (2 * x_ndc - 1) * aspect_ratio * scale;
			double y_screen = (1 - 2 * y_ndc) * scale;
			t_vec3 camera_ray = vec3_mul_matrix((t_vec3){x_screen, y_screen, -1}, view_matrix);
			t_ray ray = {scene->camera.origin, vec3_normalize(camera_ray)};
			t_hit hit = find_intersection(scene, &ray);
			if (hit.object)
				put_pixel(image, x, y, calculate_lighting(scene, hit));
			else
				put_pixel(image, x, y, (t_vec3){18, 18, 18});
		}
	}
}



void	apply_transformation(t_control control)
{
	t_keybind	*keybind;
	size_t i;

	if (control.selected.type == NONE)
		return ;
	i = 0;
	while (i < control.keybinds->size)
	{
		keybind = array_get(control.keybinds, i);
		keybind->update(keybind, &control.selected);
		i++;
	}
}

int	render_image(t_scene *scene)
{
	static int frame;

	apply_transformation(scene->mlx.control);
	if (frame++ % 10 == 0)
		raytrace(scene, &scene->mlx.image);
	frame++;
	mlx_put_image_to_window(scene->mlx.ptr, scene->mlx.win, scene->mlx.image.ptr, 0, 0);
	return (1);
}

void	render_scene(t_scene	*scene)
{
	new_image(scene->mlx.ptr, &scene->mlx.image, WIDTH, HEIGHT);
	mlx_hook(scene->mlx.win, ON_DESTROY, 0, close_win, scene);
	mlx_hook(scene->mlx.win, ON_KEY_PRESS, 1L << 0, on_key_press, scene);
	mlx_hook(scene->mlx.win, ON_KEY_RELEASE, 1L << 1, on_key_release, scene);
	mlx_mouse_hook(scene->mlx.win, on_mouse_event, scene);
	mlx_loop_hook(scene->mlx.ptr, render_image, scene);
	mlx_loop(scene->mlx.ptr);
	close_win(&scene->mlx);
}
