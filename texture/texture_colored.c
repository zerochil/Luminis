/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_colored.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:46:20 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 17:46:25 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object.h>

// 1 - v; as the texture is flipped
static double	texel_value(t_texture *texture, t_uv uv)
{
	int	x;
	int	y;

	x = (int)fabs((uv.u * texture->bump_map.width)) % texture->bump_map.width;
	y = (int)fabs(((1 - uv.v) * texture->bump_map.height))
		% texture->bump_map.height;
	return (texture->bump_map.ptr[y * texture->bump_map.width + x]);
}

t_vec3	color_new(double color)
{
	int		x;
	int		y;
	int		z;
	t_vec3	color_vec;

	z = (int)color & 0xFF;
	y = ((int)color >> 8) & 0xFF;
	x = ((int)color >> 16) & 0xFF;
	color_vec.x = x / 255.0;
	color_vec.y = y / 255.0;
	color_vec.z = z / 255.0;
	return (color_vec);
}

t_vec3	evaluate_colored_texture(t_texture *texture, struct s_hit *hit)
{
	t_uv	uv;
	double	texel;

	uv = hit->object->get_uv(hit);
	texel = texel_value(texture, uv);
	return (color_new(texel));
}
