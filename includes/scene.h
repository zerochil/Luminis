#ifndef SCENE_H
# define SCENE_H

# include <libft.h>
# include <libmath.h>
# include <color.h>
# include <object.h>
# include <mlx_image.h>

enum
{
	WIDTH = 480,
	HEIGHT = 360,
	ASPECT_RATIO = WIDTH / HEIGHT,
};

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

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_array		*lights;
	t_array		*objects;
}	t_scene;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_scene *scene;
	t_image	image;
}	t_mlx;


#endif
