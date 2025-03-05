#ifndef TEXTURES_H
# define TEXTURES_H

# include <mlx.h>
# include <mlx_image.h>
# include <libft.h>

#define IS_BUMP_TEXTURE true
#define IS_COLOR_TEXTURE false

typedef struct s_texture
{
	double	*ptr;
	int 	width;
	int 	height;
}	t_texture;

bool load_texture(void *mlx, char *filename, t_texture *texture, bool is_bump_texture);
double get_texture_uv(t_texture *texture, double u, double v);

#endif
