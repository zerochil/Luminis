#include <render.h>

t_hit find_intersection(t_scene *scene, t_ray *ray)
{
	t_hit closest_hit;
	t_object *object;
	t_array *objects;
	t_hit hit;
	size_t i;

	objects = scene->objects;
	hit.object = NULL;
	hit.distance = INFINITY;
	i = 0;
	while (i < objects->size)
	{
		object = array_get(objects, i);
		if (object->intersect(object, ray, &closest_hit))
		{
			if (closest_hit.distance < hit.distance)
				hit = closest_hit;
		}
		i++;
	}
	return (hit);
}

bool is_shadowed(t_scene *scene, t_ray ray, double light_distance)
{
	t_hit hit = find_intersection(scene, &ray);
	return (hit.object && hit.distance < light_distance);
}

typedef struct s_uv
{
	double u;
	double v;
}	t_uv;

t_uv _get_sphere_uv(t_hit hit)
{
	t_vec3 p = vec3_sub(hit.point, hit.object->origin);
	double r = hit.object->sphere.radius;
	double phi = asin(p.z);
	double theta = acos(p.x / (r * cos(phi)));
	
	// double phi = atan2(p.y, p.x);
	// double theta = asin(p.z);
	// t_uv uv = {1 - (phi + M_PI) / (2 * M_PI), (theta + M_PI / 2) / M_PI};

	t_uv uv = {theta/(2 * M_PI), 0.5 + phi/M_PI};

	return (uv);
}


t_uv get_sphere_uv(t_hit hit)
{
	//t_vec3 p = vec3_normalize(vec3_sub(hit.point, hit.object->origin));
	t_vec3 p = vec3_sub(hit.point, hit.object->origin);
	double phi = atan2(p.z, p.x);
	double theta = asin(p.y/hit.object->sphere.radius);
	t_uv uv = {1 - (phi + M_PI) / (2 * M_PI), (theta + M_PI / 2) / M_PI};
	return (uv);
}

t_uv get_cylinder_uv(t_hit hit)
{
	t_vec3 p;
	t_vec3 p_local = vec3_sub(hit.point, hit.object->origin);
	t_vec3 cx;
	t_vec3 cy;
	t_vec3 cz = hit.object->cylinder.orientation;
	create_orthonormal_basis(cz, &cx, &cy);

	p.x = vec3_dot(p_local, cx);
	p.y = vec3_dot(p_local, cy);
	p.z = vec3_dot(p_local, cz);

	double v = p.z / hit.object->cylinder.height;
	double u = (atan2(p.y, p.x) + M_PI) / (2 * M_PI);
	return (t_uv){u, v};
}

/*t_vec3 get_sphere_position_from_uv(t_uv uv, double radius)*/
/*{*/
/*    double theta = 2 * M_PI * uv.u;  // Longitude*/
/*    double phi = M_PI * uv.v;        // Latitude*/
/**/
/*    t_vec3 position;*/
/*    position.x = radius * sin(phi) * cos(theta);*/
/*    position.y = radius * sin(phi) * sin(theta);*/
/*    position.z = radius * cos(phi);*/
/**/
/*    return position;*/
/*}*/

t_color calculate_lighting(t_scene *scene, t_hit hit)
{
	t_color total_light = {0.0, 0.0, 0.0};
	t_array *lights = scene->lights;
	t_light *light;

	t_color color = hit.object->color;
	if (hit.object->type == SPHERE)
	{
		t_uv uv = get_sphere_uv(hit);
		color = color_new(get_texture_uv(&scene->texture, uv.u, uv.v));
	}

	if (hit.object->type == SPHERE)
	{
		t_vec3 p = vec3_sub(hit.point, hit.object->origin);
		double phi = acos(p.y/hit.object->sphere.radius);
		double theta = atan2(p.z, p.x);
		double scale = 20;

		double i = floor(phi / (M_PI / scale));
		double j = floor(theta / ( 2 * M_PI / scale));

		if ((int)floor(i + j) % 2 == 0)
			color = (t_color){255, 255, 255};
		else
			color = (t_color){0, 0, 0};
	}

	if (false && hit.object->type == PLANE)
	{
		double scale = 5;

		t_vec3 u;
		t_vec3 v;

		create_orthonormal_basis(hit.normal, &u, &v);
		double x = vec3_dot(hit.point, u);
		double y = vec3_dot(hit.point, v);

		int s = (int)floor(x / scale);
		int t = (int)floor(y / scale);

		if ((s + t) % 2 == 0)
			color = (t_color){255, 255, 255};
		else
			color = (t_color){0, 0, 0};
	}

	if (hit.object->type == CYLINDER)
	{
		t_uv uv = get_cylinder_uv(hit);
		
		color = color_new(get_texture_uv(&scene->texture, uv.u, uv.v));
		// double scale = 10;
		// int s = floor(uv.u * scale);
		// int t = floor(uv.v * scale);
		// if ((s + t) % 2 == 0)
		// 	color = (t_color){255, 255, 255};
		// else
		// 	color = (t_color){0, 0, 0};
	}


	if (false && hit.object->type == SPHERE)
	{
		t_uv uv = get_sphere_uv(hit);

		double coeff = .55;

		t_vec3 tangent;
		t_vec3 bitangent;

		create_orthonormal_basis(hit.normal, &tangent, &bitangent);
		
		double tex_val = get_texture_uv(&scene->texture, uv.u, uv.v);
		t_vec3 perturbed_normal = vec3_add(hit.normal, vec3_mul_scalar(bitangent, (fabs(tex_val)) * coeff));
		/*t_vec3 perturbed_normal = vec3_add(hit.normal, vec3_mul_scalar(vec3_add(tangent, bitangent), tex_val * coeff));*/
		hit.normal = vec3_add(hit.normal, perturbed_normal);
		hit.normal = vec3_normalize(hit.normal);
	}
	
	color_mul_scalar(&color, 1.0/255.0);
	t_color ambient = scene->ambient.color;
	color_mul_scalar(&ambient, 1.0/255.0);
	color_mul_scalar(&ambient, scene->ambient.intensity);
	color_mul(&ambient, &color);
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
			t_color light_color = light->color;
			color_mul_scalar(&light_color, 1.0/255.0);
			color_mul(&light_color, &color);
			double attenuation = 1.0 / (1.0 + 0.0001 * light_dist * light_dist);
			/*attenuation = 1;*/
			color_mul_scalar(&light_color, light->intensity * attenuation);
			color_mul_scalar(&light_color, diffuse_intensity * 1);
			color_add(&total_light, &light_color);

			
			t_vec3 reflect_dir = vec3_reflect(vec3_negate(light_dir), hit.normal);
			t_vec3 view_dir = vec3_normalize(vec3_sub(scene->camera.origin, hit.point));
			t_color specular_color = {1.0, 1.0, 1.0}; // white because we don't have a specular color, only metallic objects have specular color
			color_mul_scalar(&specular_color, light->intensity * attenuation);
			color_mul_scalar(&specular_color, pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), 50.0));
			color_mul_scalar(&specular_color, 0.9);
			color_add(&total_light, &specular_color);

		}
	}
	/*color_mul(&color, &total_light);*/
	color = total_light;
	color_clamp(&color);
	color_mul_scalar(&color, 255.0);
	return (color);
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
				put_pixel(image, x, y, (t_color){18, 18, 18});
		}
	}
}

int	render_image(t_mlx *mlx)
{
	static int frame;

	if (frame++ % 10 == 0)
		raytrace(&mlx->scene, &mlx->image);
	frame++;
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->image.ptr, 0, 0);
	return (1);
}

void	render_scene(t_mlx *mlx)
{
	new_image(mlx->ptr, &mlx->image, WIDTH, HEIGHT);

	mlx_hook(mlx->win, ON_DESTROY, 0, close_win, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, on_key_event, mlx);
	mlx_mouse_hook(mlx->win, on_mouse_event, mlx);
	mlx_loop_hook(mlx->ptr, render_image, mlx);
	mlx_loop(mlx->ptr);
	close_win(mlx);
}
