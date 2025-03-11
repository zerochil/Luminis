#ifndef MLX_IMAGE_H
#define MLX_IMAGE_H

#include <mlx.h>
#include <stdbool.h>
#include <stdlib.h>
#include <libmath.h>

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int 	width;
	int 	height;
}	t_image;

void	put_pixel(t_image *image, int x, int y, t_vec3 color);
void	put_image(void *mlx_ptr, void *win_ptr, t_image *image);
void    new_image(void *mlx_ptr, t_image *image, int width, int height);
bool    get_image(void *mlx_ptr, t_image *image, char *filename);
void    destroy_image(void *mlx_ptr, t_image *image);

#endif
