#ifndef ENTITY_H
#define ENTITY_H

# include <object.h>

typedef struct s_light
{
	t_vec3		origin;
	double		intensity;
	t_color		color;
} t_light;

typedef struct s_ambient
{
	double		intensity;
	t_color		color;
	bool		is_declared;
} t_ambient;

typedef struct s_camera
{
	t_vec3		origin;
	t_vec3		forward;
	t_vec3		up;
	t_vec3		right;
	double		fov;
	bool		is_declared;
} t_camera;

#endif