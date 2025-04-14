#include <object.h>

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
	return (fabs(color));
}

bool	texture_load(void *mlx_ptr, t_texture *txure, char *filename)
{
	t_image	img;
	size_t	i;
	size_t	img_size;
	int		*addr;

	if (get_image(mlx_ptr, &img, filename) == false)
		return (false);
	txure->bump_map.width = img.width;
	txure->bump_map.height = img.height;
	txure->bump_map.ptr = track_malloc(sizeof(double) * img.width * img.height);
	i = 0;
	img_size = img.width * img.height;
	addr = (int *)img.addr;
	while (i < img_size)
	{
		if (txure->type == TEXTURE_BUMP_MAP)
			txure->bump_map.ptr[i] = rgba_to_normalized_double(addr[i]);
		else
			txure->bump_map.ptr[i] = (double)addr[i];
		i++;
	}
	destroy_image(mlx_ptr, &img);
	return (true);
}

bool texture_set_type(t_texture *texture, char *type)
{
	if (ft_strcmp(type, "checker") == 0)
	{
		texture->type = TEXTURE_CHECKER;
		texture->evaluate = evaluate_checkerboard_texture;
	}
	else if (ft_strcmp(type, "bump_map") == 0)
	{
		texture->type = TEXTURE_BUMP_MAP;
		texture->evaluate = evaluate_bump_map_texture;
	}
	else if (ft_strcmp(type, "colored") == 0)
	{
		texture->type = TEXTURE_COLORED_MAP;
		texture->evaluate = evaluate_colored_texture;
	}
	else
		return (false);
	return (true);
}

t_texture *create_texture(char *name, enum e_texturetype type, t_uv_map evaluate)
{
	t_texture	*texture;

	texture = track_malloc(sizeof(t_texture));
	texture->name = name;
	texture->type = type;
	texture->evaluate = evaluate;
	return (texture);
}
