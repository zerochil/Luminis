#ifndef TEXTURES_H
# define TEXTURES_H

# include <mlx.h>
# include <mlx_image.h>
# include <libft.h>

typedef struct s_texture
{
	double	*ptr;
	int 	width;
	int 	height;
}	t_texture;

bool load_texture(void *mlx, char *filename, t_texture *texture);

#endif
