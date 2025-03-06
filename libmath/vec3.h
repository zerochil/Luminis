#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdbool.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_mul(t_vec3 a, t_vec3 b);
t_vec3	vec3_div(t_vec3 a, t_vec3 b);
t_vec3	vec3_add_scalar(t_vec3 a, double b);
t_vec3	vec3_sub_scalar(t_vec3 a, double b);
t_vec3	vec3_mul_scalar(t_vec3 a, double b);
t_vec3	vec3_div_scalar(t_vec3 a, double b);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_length(t_vec3 a);
t_vec3	vec3_normalize(t_vec3 a);
t_vec3  vec3_negate(t_vec3 a);
void	vec3_rotateX(t_vec3 *vec, double angle);
void	vec3_rotateY(t_vec3 *vec, double angle);
t_vec3 vec3_reflect(t_vec3 v, t_vec3 n);
t_vec3 vec3_lerp(t_vec3 a, t_vec3 b, double t);
void create_orthonormal_basis(t_vec3 fixed, t_vec3 *b1, t_vec3 *b2);

bool vec3_compare(t_vec3 a, t_vec3 b);

#endif
