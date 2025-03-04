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
	t_color color = {0.0, 0.0, 0.0};
	t_array *lights = scene->lights;
	t_light *light;
	t_vec3 light_direction;
	double diffuse_intensity;
	t_color light_color;

	t_color tmp = color_mul_scalar(hit.object->color, 1.0/255.0);
	t_color ambient = color_mul_scalar(scene->ambient.color, 1.0/255.0);
	color.r += tmp.r * ambient.r * scene->ambient.intensity;
	color.g += tmp.g * ambient.g * scene->ambient.intensity;
	color.b += tmp.b * ambient.b * scene->ambient.intensity;
	for (size_t i = 0; i < lights->size; i++)
	{

		light = array_get(lights, i);
		light_direction = vec3_normalize(vec3_sub(light->origin, hit.point));
		double light_distance = vec3_length(vec3_sub(light->origin, hit.point));
		if (is_shadowed(scene, (t_ray){vec3_add(hit.point, vec3_mul_scalar(hit.normal, EPSILON * 1000)), light_direction}, light_distance))
		{
			/*t_color shadow_ambient = color_mul_scalar(light_color, 0.001 * light->intensity);*/
			/*color.r += tmp.r * shadow_ambient.r;*/
			/*color.g += tmp.g * shadow_ambient.g;*/
			/*color.b += tmp.b * shadow_ambient.b;*/
			/*color_clamp(&color);*/
			continue;
		}
		diffuse_intensity = fmax(vec3_dot(hit.normal, light_direction), 0);
		if (diffuse_intensity > 0)
		{
			light_color = color_mul_scalar(light->color, 1.0/255.0);
			light_color = color_mul_scalar(light_color, light->intensity * (1.0 / (1.0 + 0.001 * light_distance * light_distance)));
			color.r += tmp.r * light_color.r * diffuse_intensity;
			color.g += tmp.g * light_color.g * diffuse_intensity;
			color.b += tmp.b * light_color.b * diffuse_intensity;
		}
		color_clamp(&color);
	}
	return (color_mul_scalar(color, 255));
}

void	print_matrix(t_matrix *matrix)
{
	printf("-------------------------------\n");
	for(int y=0; y<4;y++)
	{
		for(int x=0; x<4; x++)
			printf("% 3.3f ", matrix->data[y * 4 + x]);
		printf("\n");
	}
	printf("-------------------------------\n");
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
