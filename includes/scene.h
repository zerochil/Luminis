#ifndef SCENE_H
# define SCENE_H

# include <libft.h>
# include <libmath.h>
# include <object.h>
# include <mlx_image.h>
# include <texture.h>
# include <material.h>

enum
{
	WIDTH = 480,
	HEIGHT = 360,
	ASPECT_RATIO = WIDTH / HEIGHT,
};

typedef struct s_light
{
	t_vec3		origin; // this is so confusing, should be position as most other definition (like ray, sphere, etc) have a position field instead of origin
	double		intensity;
	t_vec3		color;
} t_light;

typedef struct s_ambient
{
	double		intensity;
	t_vec3		color;
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

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_array		*lights;
	t_array		*objects;
	t_array		*materials;
	t_texture	texture;
}	t_scene;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_scene scene;
	t_image	image;
}	t_mlx;


#endif
