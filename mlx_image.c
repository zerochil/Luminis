/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:26 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 17:56:27 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx_image.h>

void	put_pixel(t_image *image, int x, int y, t_vec3 color)
{
	int	i;

	i = (y * image->line_len) + (x * (image->bpp / 8));
	image->addr[i] = color.z;
	image->addr[i + 1] = color.y;
	image->addr[i + 2] = color.x;
	image->addr[i + 3] = 0x00;
}

void	put_image(void *mlx_ptr, void *win_ptr, t_image *image)
{
	mlx_put_image_to_window(mlx_ptr, win_ptr, image->ptr, 0, 0);
}

void	new_image(void *mlx_ptr, t_image *image, int width, int height)
{
	image->ptr = mlx_new_image(mlx_ptr, width, height);
	image->addr = mlx_get_data_addr(image->ptr, &image->bpp, &image->line_len,
			&image->endian);
}

bool	get_image(void *mlx_ptr, t_image *image, char *filename)
{
	image->ptr = mlx_xpm_file_to_image(mlx_ptr, filename, &image->width,
			&image->height);
	if (image->ptr == NULL)
		return (false);
	image->addr = mlx_get_data_addr(image->ptr, &image->bpp, &image->line_len,
			&image->endian);
	return (true);
}

void	destroy_image(void *mlx_ptr, t_image *image)
{
	mlx_destroy_image(mlx_ptr, image->ptr);
}
