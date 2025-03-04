#include <render.h>

void window_init(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, 480, 360, "Luminis");
}

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

void put_pixel(t_image *image, int x, int y, t_color color)
{
	int i;

	i = (y * image->line_len) + (x * (image->bpp / 8));
	image->addr[i] = color.b;
	image->addr[i + 1] = color.g;
	image->addr[i + 2] = color.r;
	image->addr[i + 3] = 0x00;
}

bool is_shadowed(t_scene *scene, t_ray ray, double light_distance)
{
	t_hit hit = find_intersection(scene, &ray);
	return (hit.object && hit.distance < light_distance);
}

t_color calculate_lighting(t_scene *scene, t_hit hit)
{
	t_color total_light = {0.0, 0.0, 0.0};
	t_array *lights = scene->lights;
	t_light *light;

	t_color color = hit.object->color;
	color_mul_scalar(&color, 1.0/255.0);
	t_color ambient = scene->ambient.color;
	color_mul_scalar(&ambient, 1.0/255.0);
	color_mul_scalar(&ambient, scene->ambient.intensity);
	total_light = ambient;
	for (size_t i = 0; i < lights->size; i++)
	{
		light = array_get(lights, i);
		t_vec3 light_dir = vec3_normalize(vec3_sub(light->origin, hit.point));
		double light_dist = vec3_length(vec3_sub(light->origin, hit.point));
		if (is_shadowed(scene, (t_ray){vec3_add(hit.point, vec3_mul_scalar(hit.normal, EPSILON * 1000)), light_dir}, light_dist))
			continue;

		double diffuse_intensity = fmax(vec3_dot(hit.normal, light_dir), 0.0);
		double attenuation = 1.0 / (1.0 + 0.01 * light_dist + 0.001 * light_dist * light_dist);
		if (diffuse_intensity > 0.0)
		{
			t_color light_color = light->color;
			color_mul_scalar(&light_color, 1.0/255.0);
			/*double attenuation = 1.0 / (1.0 + light_dist * light_dist);*/

			color_mul_scalar(&light_color, light->intensity * attenuation);
			color_mul_scalar(&light_color, diffuse_intensity);
			color_add(&total_light, &light_color);
		}

		t_vec3 reflect_dir = vec3_reflect(vec3_negate(light_dir), hit.normal);
		t_vec3 view_dir = vec3_normalize(vec3_sub(scene->camera.origin, hit.point)); // you can avoid some calculations by storing the normalized view direction in the hit struct
		double specular_intensity = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), 30.0);
		t_color specular_color = {1.0, 1.0, 1.0}; // white because we don't have a specular color, only metallic objects have specular color
		color_mul_scalar(&specular_color, light->intensity);
		color_mul_scalar(&specular_color, specular_intensity * 0.5);
		color_add(&total_light, &specular_color);
	}

	color_mul(&color, &total_light);

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

void	render_image(t_mlx *mlx, t_scene *scene)
{
	mlx->image.ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->image.addr = mlx_get_data_addr(mlx->image.ptr, &mlx->image.bpp, &mlx->image.line_len, &mlx->image.endian);
	raytrace(scene, &mlx->image);
	//printf("Rendering complete\n");
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->image.ptr, 0, 0);
}

int		render_next_frame(t_mlx *mlx)
{
	t_scene *scene = mlx->scene;

	render_image(mlx, scene);
	return (1);
}

void	render_scene(t_scene *scene)
{
	t_mlx		mlx;

	window_init(&mlx);
	mlx.scene = scene;
	mlx_hook(mlx.win, ON_DESTROY, 0, close_win, &mlx);
	mlx_hook(mlx.win, ON_KEYDOWN, 1L << 0, on_key_event, &mlx);
	mlx_mouse_hook(mlx.win, on_mouse_event, &mlx);
	mlx_loop_hook(mlx.ptr, render_next_frame, &mlx);
	mlx_loop(mlx.ptr);
	close_win(&mlx);
}
