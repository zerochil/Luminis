#ifndef SCENE_H
# define SCENE_H

# include <libft.h>
# include <libmath.h>
# include <entity.h>
# include <mlx_image.h>
# include <texture.h>
# include <keybind.h>

enum
{
	WIDTH = 480,
	HEIGHT = 360,
	ASPECT_RATIO = WIDTH / HEIGHT,
};

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_array		*lights;
	t_array		*objects;
	t_array		*materials;
	t_texture	texture;
}	t_scene;

typedef struct s_control
{
	t_entity	selected;
	t_array		*keybinds;
} t_control;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_image	image;
	t_scene scene;
	t_control control;
}	t_mlx;

#endif
