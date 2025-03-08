#include "libmath.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result);
}

t_vec3	vec3_div(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	return (result);
}

t_vec3	vec3_add_scalar(t_vec3 a, double b)
{
	t_vec3	result;

	result.x = a.x + b;
	result.y = a.y + b;
	result.z = a.z + b;
	return (result);
}

t_vec3	vec3_sub_scalar(t_vec3 a, double b)
{
	t_vec3	result;

	result.x = a.x - b;
	result.y = a.y - b;
	result.z = a.z - b;
	return (result);
}

t_vec3	vec3_mul_scalar(t_vec3 a, double b)
{
	t_vec3	result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return (result);
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3	vec3_div_scalar(t_vec3 a, double b)
{
	t_vec3	result;

	result.x = a.x / b; // division by zero is not handled
	result.y = a.y / b;
	result.z = a.z / b;
	return (result);
}

double	vec3_length(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	vec3_normalize(t_vec3 a)
{
	double	length;

	length = vec3_length(a);
	return (vec3_div_scalar(a, length));
}

t_vec3  vec3_negate(t_vec3 a)
{
	t_vec3 result;

	result.x = -a.x;
	result.y = -a.y;
	result.z = -a.z;
	return (result);
}

bool vec3_compare(t_vec3 a, t_vec3 b)
{
	return (float_eq(a.x, b.x) && float_eq(a.y, b.y) && float_eq(a.z, b.z));
}

t_vec3 vec3_reflect(t_vec3 v, t_vec3 n)
{
	return (vec3_sub(v, vec3_mul_scalar(n, 2 * vec3_dot(v, n))));
}
void	vec3_rotateY(t_vec3 *vec, double angle)
{
	double x;
	double z;

	angle = angle * (M_PI / 180);
	x = vec->x;
	z = vec->z;
	vec->x = x * cos(angle) + z * sin(angle);
    vec->z = -x * sin(angle) + z * cos(angle);
}

void	vec3_rotateX(t_vec3 *vec, double angle)
{
	double y;
	double z;

	angle = angle * (M_PI / 180);
	y = vec->y;
	z = vec->z;
	
    vec->y = y * cos(angle) - z * sin(angle);
    vec->z = y * sin(angle) + z * cos(angle);
}

void	rotate_dev(t_vec3 *vec, t_vec3 axis, double angle)
{
	angle = angle * (M_PI / 180);
	double half_theta = sin(angle / 2);
	double qx = axis.x * half_theta;
	double qy = axis.y * half_theta;
	double qz = axis.z * half_theta;
	double qw = cos(angle / 2);

	//p' = q * p * conj(q);
	double x = (1 - 2 * qy * qy - 2 * qz * qz) * vec->x;
	x += (2 * qx * qy - 2 * qw * qz) * vec->y;
	x += (2 * qx * qz + 2 * qw * qy) * vec->z;

	double y = (2 * qx * qy + 2 * qw * qz) * vec->x;
	y += (1 - 2 * qx * qx - 2 * qz * qz) * vec->y;
	y += (2 * qy * qz - 2 * qw * qx) * vec->z;

	double z = (2 * qx * qz - 2 * qw * qy) * vec->x;
	z += (2 * qy * qz + 2 * qw * qx) * vec->y;
	z += (1 - 2 * qx * qx - 2 * qy * qy) * vec->z;

	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void create_orthonormal_basis(t_vec3 n, t_vec3 *b1, t_vec3 *b2) {
    if (n.z < -0.9999999) {
        *b1 = (t_vec3){1.0, 0.0, 0.0};
        *b2 = (t_vec3){0.0, 1.0, 0.0};
        return;
    }
    float a = 1.0 / (1.0 + n.z);
    float b = -n.x * n.y * a;
    *b1 = (t_vec3){1.0 - n.x * n.x * a, b, -n.x};
    *b2 = (t_vec3){b, 1.0 - n.y * n.y * a, -n.y};
}

t_vec3 vec3_lerp(t_vec3 a, t_vec3 b, double t)
{
	return (vec3_add(vec3_mul_scalar(a, 1 - t), vec3_mul_scalar(b, t)));
}
