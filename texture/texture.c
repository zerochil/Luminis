#include <texture.h>

double	rgba_to_normalized_double(int rgba)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	double			color;

	red = (rgba >> 24) & 0xFF;
	green = (rgba >> 16) & 0xFF;
	blue = (rgba >> 8) & 0xFF;
	color = (red + green + blue) / 255.0 / 3.0;
	return (color);
}

bool	load_texture(void *mlx, char *filename, t_texture *txure, bool is_bump_texture)
{
	t_image	img;
	size_t	i;
	size_t	img_size;
	int		*addr;

	if (get_image(mlx, &img, filename) == false)
		return (false);
	txure->bump_map.width = img.width;
	txure->bump_map.height = img.height;
	txure->bump_map.ptr = track_malloc(sizeof(double) * img.width * img.height);
	i = 0;
	img_size = img.width * img.height;
	addr = (int *)img.addr;
	while (i < img_size)
	{
		if (is_bump_texture)
			txure->bump_map.ptr[i] = rgba_to_normalized_double(addr[i]);
		else
			txure->bump_map.ptr[i] = (double)addr[i];
		i++;
	}
	destroy_image(mlx, &img);
	return (true);
}

t_texture *create_texture(char *name, enum e_texturetype type, uv_map evaluate)
{
	t_texture	*texture;

	texture = track_malloc(sizeof(t_texture));
	texture->name = name;
	texture->type = type;
	texture->evaluate = evaluate;
	return (texture);
}
