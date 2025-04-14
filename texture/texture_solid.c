/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_solid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:46:20 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 17:46:27 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object.h>

t_vec3	evaluate_solid_texture(t_texture *texture, t_hit *hit)
{
	(void)texture;
	(void)hit;
	return (hit->object->color);
}
