/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_checkerboard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:46:20 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 17:46:26 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object.h>

t_vec3	evaluate_checkerboard_texture(t_texture *texture, struct s_hit *hit)
{
	t_uv	uv;

	uv = hit->object->get_uv(hit);
	uv.u = floor(uv.u * texture->checker.scale);
	uv.v = floor(uv.v * texture->checker.scale);
	if ((int)floor(uv.u + uv.v) % 2 == 0)
		return (texture->checker.color1);
	return (texture->checker.color2);
}
