#include "texture.h"

double rgba_to_normalized_double(int rgba)
{
	unsigned char red = (rgba >> 24) & 0xFF;
	unsigned char green = (rgba >> 16) & 0xFF;
	unsigned char blue = (rgba >> 8) & 0xFF;
	double color = (red + green + blue) / 255.0 / 3.0;
	return (color);
}

bool load_texture(void *mlx, char *filename, t_texture *texture)
{
	t_image image;
	size_t i;
	size_t j;

	if (get_image(mlx, &image, filename) == false)
		return (false);
	texture->width = image.width;
	texture->height = image.height;
	texture->ptr = track_malloc(sizeof(double) * image.width * image.height);
	i = 0;
	j = 0;
	while (i < (size_t)image.width * image.height)
	{
		texture->ptr[i] = rgba_to_normalized_double(*(int *)(image.addr + j));
		i++;
		j += 4;
	}
	destroy_image(mlx, &image);
	return (true);
}
