#ifndef OBJECT_H
# define OBJECT_H
	
# include <libmath.h>
# include <color.h>
# include <libft.h>

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

typedef bool (*t_intersect)(t_object*, t_ray*, t_hit*);

struct s_object
{
	t_color		color;
	enum e_object	type;
	t_vec3		origin;
	t_intersect intersect;
	union {
		struct {
			double		radius;
		} sphere;
		struct {
			t_vec3		normal;
		} plane;
		struct {
			t_vec3		orientation;
			double		radius;
			double		height;
		} cylinder;
		struct
		{
			t_vec3	orientation;
			double	angle;
		}	cone;
	};
};

t_object	*object_create(enum e_object type);

#endif
