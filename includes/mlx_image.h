/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:53:13 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 15:53:21 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_IMAGE_H
# define MLX_IMAGE_H

# include <libmath.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_image;

void		put_pixel(t_image *image, int x, int y, t_vec3 color);
void		put_image(void *mlx_ptr, void *win_ptr, t_image *image);
void		new_image(void *mlx_ptr, t_image *image, int width, int height);
bool		get_image(void *mlx_ptr, t_image *image, char *filename);
void		destroy_image(void *mlx_ptr, t_image *image);

#endif
