/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bumpmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:46:20 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 17:48:52 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object.h>

static double	bump_value(t_texture *texture, t_uv uv)
{
	int	x;
	int	y;

	x = (int)fabs((uv.u * texture->bump_map.width)) % texture->bump_map.width;
	y = (int)fabs(((1 - uv.v) * texture->bump_map.height))
		% texture->bump_map.height;
	return (texture->bump_map.ptr[y * texture->bump_map.width + x]);
}

static void	calculate_perturbed_normal(struct s_hit *hit, double bump)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	perturbed_normal;
	double	coeff;

	coeff = .9;
	create_orthonormal_basis(hit->normal, &tangent, &bitangent);
	perturbed_normal = vec3_add(hit->normal,
			vec3_mul_scalar(bitangent, bump * coeff));
	hit->normal = vec3_add(hit->normal, perturbed_normal);
	hit->normal = vec3_normalize(hit->normal);
}

t_vec3	evaluate_bump_map_texture(t_texture *texture, struct s_hit *hit)
{
	t_uv	uv;
	double	bump;

	uv = hit->object->get_uv(hit);
	bump = bump_value(texture, uv);
	calculate_perturbed_normal(hit, bump);
	return (hit->object->color);
}
