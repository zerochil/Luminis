/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:53:13 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 15:53:20 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include <libft.h>
# include <libmath.h>
# include <mlx_image.h>

# define IS_BUMP_TEXTURE true
# define IS_COLOR_TEXTURE false

enum							e_texturetype
{
	TEXTURE_SOLID,
	TEXTURE_CHECKER,
	TEXTURE_BUMP_MAP,
	TEXTURE_COLORED_MAP
};

struct							s_solidtexture
{
	t_vec3						color;
};

struct							s_checkertexture
{
	t_vec3						color1;
	t_vec3						color2;
	double						scale;
};

struct							s_bumpmaptexture
{
	double						*ptr;
	int							width;
	int							height;
};

enum							e_object
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	CONE,
	RECTANGLE,
};

typedef struct s_object			t_object;

typedef struct s_hit
{
	t_vec3						point;
	t_vec3						normal;
	double						distance;
	t_object					*object;
}								t_hit;

typedef struct s_ray
{
	t_vec3						origin;
	t_vec3						direction;
}								t_ray;

typedef struct s_uv
{
	double						u;
	double						v;
}								t_uv;

typedef bool					(*t_intersect)(t_object *, t_ray *, t_hit *);
typedef t_uv					(*t_object_uv)(t_hit *hit);
typedef struct s_texture		t_texture;
typedef t_vec3					(*t_uv_map)(struct s_texture *self, t_hit *hit);

struct							s_texture
{
	char						*name;
	enum e_texturetype			type;
	union
	{
		struct s_solidtexture	solid;
		struct s_checkertexture	checker;
		struct s_bumpmaptexture	bump_map;
	};
	t_uv_map					evaluate;
};

struct							s_object
{
	t_vec3						color;
	enum e_object				type;
	t_vec3						origin;
	t_vec3						orientation;
	double						radius;
	double						width;
	double						height;
	double						angle;
	t_texture					*texture;
	char						*texture_name;
	t_intersect					intersect;
	t_object_uv					get_uv;
};

t_object	*object_create(enum e_object type);
bool		texture_load(void *mlx, t_texture *texture, char *filename);
bool		texture_set_type(t_texture *texture, char *type);
t_texture	*create_texture(char *name, enum e_texturetype type,
				t_uv_map evaluate);
t_vec3		evaluate_solid_texture(t_texture *texture, t_hit *hit);
t_vec3		evaluate_bump_map_texture( t_texture *texture, struct s_hit *hit);
t_vec3		evaluate_checkerboard_texture(
				t_texture *texture, struct s_hit *hit);
t_vec3		evaluate_colored_texture(t_texture *texture, struct s_hit *hit);

typedef struct s_scene			t_scene;
typedef struct s_ray			t_ray;
typedef struct s_hit			t_hit;
t_hit		find_intersection(t_scene *scene, t_ray *ray);

void	print_object(t_object *obj);

#endif
