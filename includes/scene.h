#ifndef SCENE_H
# define SCENE_H

# include <libft.h>
# include <libmath.h>

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
} t_color;

typedef struct s_object
{
	t_vec3		origin;
	t_vec3		rotation;
	float		size;
	t_color		color;
	char		type;
} t_object;

typedef struct s_light
{
	t_vec3		origin;
	float		intensity;
	t_vec3		color;
} t_light;

typedef struct s_ambient
{
	float		intensity;
	t_vec3		color;
} t_ambient;

typedef struct s_camera
{
	t_vec3		origin;
	t_vec3		direction;
	t_vec3		up;
	t_vec3		right;
	float		fov;
} t_camera;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_array		lights;
	t_array		objects;
}	t_scene;

#endif
