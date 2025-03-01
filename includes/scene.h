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

enum e_object
{
	SPHERE = 0,
	PLANE,
	CYLINDER
};

typedef struct s_object
{
	t_color		color;
	enum e_object	type;
	t_vec3		origin;
	union {
		struct {
			double		radius;
		} sphere;
		struct {
			t_vec3		orientation;
		} plane;
		struct {
			t_vec3		orientaiton;
			double		radius;
			double		height;
		} cylinder;
	};
} t_object;

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
	t_vec3		direction;
	t_vec3		up;
	t_vec3		right;
	double		fov;
	bool		is_declared;
} t_camera;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_array		*lights;
	t_array		*objects;
}	t_scene;

#endif
