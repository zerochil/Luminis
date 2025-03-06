#include "texture.h"

double rgba_to_normalized_double(int rgba)
{
	unsigned char red = (rgba >> 24) & 0xFF;
	unsigned char green = (rgba >> 16) & 0xFF;
	unsigned char blue = (rgba >> 8) & 0xFF;
	double color = (red + green + blue) / 255.0 / 3.0;
	return (color);
}

bool load_texture(void *mlx, char *filename, t_texture *texture, bool is_bump_texture)
{
	t_image image;
	size_t i;
	size_t image_size;
	int    *addr;

	if (get_image(mlx, &image, filename) == false)
		return (false);
	texture->width = image.width;
	texture->height = image.height;
	texture->ptr = track_malloc(sizeof(double) * image.width * image.height);
	i = 0;
	image_size = image.width * image.height;
	addr = (int *)image.addr;
	while (i < image_size)
	{
		if (is_bump_texture)
			texture->ptr[i] = rgba_to_normalized_double(addr[i]);
		else
			texture->ptr[i] = (double)addr[i];
		i++;
	}
	destroy_image(mlx, &image);
	return (true);
}

// 1 - v because the texture is flipped
double get_texture_uv(t_texture *texture, double u, double v)
{
	int x = (int)(u * texture->width) % texture->width;
	int y = (int)((1 - v) * texture->height) % texture->height;
	if (x < 0)
		x = 0;
	if (x >= texture->width)
		x = texture->width - 1;
	if (y < 0)
		y = 0;
	if (y >= texture->height)
		y = texture->height - 1;
	return (texture->ptr[y * texture->width + x]);
}
