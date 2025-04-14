#ifndef LIGHTING_H
# define LIGHTING_H

# include <mlx.h>
# include <scene.h>
# include <utils.h>

typedef struct s_light_data
{
	t_light	*light;
	t_vec3	obj_color;
	double	intensity;

	t_vec3	light_dir;
	double	light_dist;
	t_vec3	light_color;

	t_vec3	specular;
	t_vec3	reflect_dir;
	t_vec3	view_dir;

	double	attenuation;
	double	diffuse_intensity;
}			t_light_data;

t_vec3		calculate_lighting(t_scene *scene, t_hit *hit);

#endif
