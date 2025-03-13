#include <render.h>

bool is_shadowed(t_scene *scene, t_light *light, t_hit *hit)
{
	t_ray shadow_ray;
	double light_distance;
	t_hit light_hit;

	shadow_ray = (t_ray){
		.origin = vec3_add(hit->point, vec3_mul_scalar(hit->normal, EPSILON * 10000)),
		.direction = vec3_sub(light->origin, hit->point),
	};
	light_distance = vec3_length(shadow_ray.direction);
	shadow_ray.direction = vec3_mul_scalar(shadow_ray.direction, 1 / light_distance);
	light_hit = find_intersection(scene, &shadow_ray);
	return (light_hit.object && light_hit.distance < light_distance);
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

	t_vec3 color = hit.object->texture->evaluate(hit.object->texture, &hit);
	
	t_vec3 ambient = scene->ambient.color;
	ambient = vec3_mul_scalar(ambient, scene->ambient.intensity);
	ambient = vec3_mul(ambient, color);
	total_light = ambient;
	for (size_t i = 0; i < lights->size; i++)
	{
		light = array_get(lights, i);
		t_vec3 light_dir = vec3_normalize(vec3_sub(light->origin, hit.point));
		double light_dist = vec3_length(vec3_sub(light->origin, hit.point));
		if (is_shadowed(scene, light, &hit))
			continue;
		double diffuse_intensity = fmax(vec3_dot(hit.normal, light_dir), 0.0);
		if (diffuse_intensity > 0.0)
		{
			t_vec3 light_color = light->color;
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

#ifdef THREADS

#include <pthread.h>

typedef struct s_data
{
    pthread_t   tid;
    t_scene *scene;
    int     start_x;
    int     start_y;
    int     end_x;
    int     end_y;
} t_data;

void raytrace_thread(t_data *data)
{
	t_scene *scene = data->scene;
    double aspect_ratio = (double)WIDTH / HEIGHT;
	double scale = tan((scene->camera.fov * M_PI / 180.0) / 2.0);
	t_matrix view_matrix = camera_matrix(scene->camera);

	for (int y = data->start_y; y < data->end_y; y++)
	{
		for (int x = data->start_x; x < data->end_x; x++)
		{
			double x_ndc = (x + 0.5) / WIDTH;
			double y_ndc = (y + 0.5) / HEIGHT;
			double x_screen = (2 * x_ndc - 1) * aspect_ratio * scale;
			double y_screen = (1 - 2 * y_ndc) * scale;
			t_vec3 camera_ray = vec3_mul_matrix((t_vec3){x_screen, y_screen, -1}, view_matrix);
			t_ray ray = {scene->camera.origin, vec3_normalize(camera_ray)};
			t_hit hit = find_intersection(scene, &ray);
			if (hit.object)
				put_pixel(&scene->mlx.image, x, y, calculate_lighting(scene, hit));
			else
				put_pixel(&scene->mlx.image, x, y, (t_vec3){18, 18, 18});
		}
	}
}

t_array *create_threads_data(int width, int height, int nb_threads)
{
    t_array *threads;
    t_data  *data;
	int i = 0;

    threads = array_create();
    while (i < nb_threads)
    {
        data = track_malloc(sizeof(t_data));
        data->start_x = 0;
        data->end_x = width;
        data->start_y = i * (height / nb_threads);
        data->end_y = (i + 1) * (height / nb_threads);
        array_push(threads, data);
        i++; 
    }
    return (threads);
}

void raytrace(t_scene *scene)
{
    static t_array *threads;
	t_data	*data;
	int		nb_threads = 40;
	int		i = 0;

	if (threads == NULL)
    	threads = create_threads_data(WIDTH, HEIGHT, nb_threads);
	while (i < nb_threads)
	{
		data = array_get(threads, i);
		data->scene = scene;
		pthread_create(&data->tid, NULL, (void*)raytrace_thread, data);
		i++;
	}
	i = 0;
	while (i < nb_threads)
	{
		data = array_get(threads, i);
		pthread_join(data->tid, NULL);
		i++;
	}
}
#else

void raytrace(t_scene *scene)
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
			/*(void)hit;*/
			(void)scene;
			(void)image;
			if (hit.object)
				put_pixel(&scene->mlx.image, x, y, calculate_lighting(scene, hit));
			else
				put_pixel(&scene->mlx.image, x, y, (t_vec3){18, 18, 18});
		}
	}
}

#endif

bool	apply_transformation(t_control control)
{
	t_keybind	*keybind;
	bool		state_changed;
	size_t i;

	if (control.selected.type == NONE)
		return (false);
	i = 0;
	state_changed = false;
	while (i < control.keybinds->size)
	{
		keybind = array_get(control.keybinds, i);
		if (keybind->dir_flag != 0)
		{
			keybind->update(keybind, &control.selected);
			state_changed = true;
		} 
		i++;
	}
	return (state_changed);
}

int	render_image(t_scene *scene)
{
	static bool first = true;

	if (apply_transformation(scene->mlx.control) || first)
	{
		raytrace(scene);
		first = false;
	}
	mlx_put_image_to_window(scene->mlx.ptr, scene->mlx.win, scene->mlx.image.ptr, 0, 0);
	return (1);
}

void	render_scene(t_scene	*scene)
{
	new_image(scene->mlx.ptr, &scene->mlx.image, WIDTH, HEIGHT);
	mlx_hook(scene->mlx.win, ON_DESTROY, 0, close_win, &scene->mlx);
	mlx_hook(scene->mlx.win, ON_KEY_PRESS, 1L << 0, on_key_press, scene);
	mlx_hook(scene->mlx.win, ON_KEY_RELEASE, 1L << 1, on_key_release, scene);
	mlx_mouse_hook(scene->mlx.win, on_mouse_event, scene);
	mlx_loop_hook(scene->mlx.ptr, render_image, scene);
	mlx_loop(scene->mlx.ptr);
	close_win(&scene->mlx);
}
