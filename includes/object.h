#ifndef OBJECT_H
# define OBJECT_H
	
# include <libmath.h>
# include <libft.h>
# include <material.h>

enum e_object
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	CONE,
};

typedef struct s_object t_object;

typedef struct s_hit
{
	t_vec3		point;
	t_vec3		normal;
	double		distance;
	t_object	*object;
} t_hit;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
} t_ray;


typedef struct s_uv
{
	double u;
	double v;
}	t_uv;

typedef bool (*t_intersect)(t_object*, t_ray*, t_hit*);
typedef t_uv (*t_object_uv)(t_hit *hit);

struct s_object
{
	t_vec3		color;
	enum e_object	type;
	t_vec3		origin;
	t_vec3		orientation;
	double 		radius;
	double		height;
	double		angle;
	t_material  material;
	t_intersect intersect;
	t_object_uv get_uv;
};

t_object	*object_create(enum e_object type);

#endif
