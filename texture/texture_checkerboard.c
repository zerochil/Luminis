/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_checkerboard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:46:20 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 17:46:20 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object.h>

t_vec3	evaluate_checkerboard_texture(t_texture *texture, struct s_hit *hit)
{
	t_uv	uv;
	int		u;
	int		v;

	uv = hit->object->get_uv(hit);
	u = floor(uv.u * texture->checker.scale);
	v = floor(uv.v * texture->checker.scale);
	if ((u + v) % 2 == 0)
		return (texture->checker.color1);
	return (texture->checker.color2);
}
