#ifndef RENDER_H
#define RENDER_H

#include <scene.h>
#include <mlx.h>

enum
{
	WIDTH = 480,
	HEIGHT = 360,
	ASPECT_RATIO = WIDTH / HEIGHT,
};

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_image	image;
}	t_mlx;

void render_scene(t_scene *scene);

#endif
