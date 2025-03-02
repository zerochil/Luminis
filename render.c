#include <render.h>

void window_init(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, 480, 360, "Luminis");
}

int	close_win(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->image.ptr);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
		close_win(mlx);
	return (0);
}


t_matrix camera_matrix(t_camera camera)
{
	t_matrix matrix;
	t_vec3 translation;
	t_vec3 negated;

	negated = vec3_negate(camera.origin);
	translation.x = vec3_dot(camera.right, negated);
	translation.y = vec3_dot(camera.up, negated);
	translation.z = vec3_dot(camera.forward, negated);
	matrix = matrix_translate(translation);
	matrix = matrix_multiply(matrix, matrix_rotate(camera.right, camera.up, camera.forward));
	return (matrix);
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

t_color calculate_lighting(t_scene *scene, t_hit hit)
{
	t_color color = {0, 0, 0};
	t_array *lights = scene->lights;
	t_light *light;
	t_vec3 light_direction;
	double diffuse_intensity;
	t_color light_color;

	t_color tmp = color_mul_scalar(hit.object->color, 1.0/255.0);
	for (size_t i = 0; i < lights->size; i++)
	{
		light = array_get(lights, i);
		light_direction = vec3_normalize(vec3_sub(light->origin, hit.point));
		diffuse_intensity = fmax(vec3_dot(hit.normal, light_direction), 0);
		if (diffuse_intensity > 0)
		{
			light_color = color_mul_scalar(light->color, 1.0/255.0);
			light_color = color_mul_scalar(light_color, light->intensity);
			color.r += tmp.r * light_color.r * diffuse_intensity;
			color.g += tmp.g * light_color.g * diffuse_intensity;
			color.b += tmp.b * light_color.b * diffuse_intensity;
		}
	}
	t_color ambient = color_mul_scalar(scene->ambient.color, 1.0/255.0);
	color.r += tmp.r * ambient.r * scene->ambient.intensity;
	color.g += tmp.g * ambient.g * scene->ambient.intensity;
	color.b += tmp.b * ambient.b * scene->ambient.intensity;
	if (color.r > 1)
	{
		printf("color.r: %f\n", color.r);
	}
	color_clamp(&color);
	return (color_mul_scalar(color, 255));
}

void raytrace(t_scene *scene, t_image *image)
{
	t_matrix view_matrix = camera_matrix(scene->camera);
	double aspect_ratio = (double)WIDTH / HEIGHT;
	double scale = tan(scene->camera.fov / 2);

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			double x_ndc = (x + 0.5) / WIDTH;
			double y_ndc = (y + 0.5) / HEIGHT;
			double x_screen = (2 * x_ndc - 1) * aspect_ratio * scale;
			double y_screen = (1 - 2 * y_ndc) * scale;
			t_vec3 direction = matrix_mult_vec3(view_matrix, (t_vec3){x_screen, y_screen, -1});
			t_ray ray = {scene->camera.origin, vec3_normalize(direction)};
			t_hit hit = find_intersection(scene, &ray);
			if (hit.object)
			{
				// Calculate lighting by iterating over all lights and summing their contributions
				t_color color = calculate_lighting(scene, hit);
				put_pixel(image, x, y, color);
			}
			else
			{
				put_pixel(image, x, y, (t_color){18, 18, 18});
			}
		}
	}
}

void	render_image(t_mlx *mlx, t_scene *scene)
{
	mlx->image.ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->image.addr = mlx_get_data_addr(mlx->image.ptr, &mlx->image.bpp, &mlx->image.line_len, &mlx->image.endian);
	raytrace(scene, &mlx->image);
	printf("Rendering complete\n");
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->image.ptr, 0, 0);
}

void	render_scene(t_scene *scene)
{
	t_mlx		mlx;

	window_init(&mlx);
	mlx_hook(mlx.win, 17, 0, close_win, &mlx);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	render_image(&mlx, scene);
	mlx_loop(mlx.ptr);
	close_win(&mlx);
}
