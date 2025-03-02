#include "vec3.h"

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

t_vec3	vec3_div_scalar(t_vec3 a, double b)
{
	t_vec3	result;

	result.x = a.x / b; // division by zero is not handled
	result.y = a.y / b;
	result.z = a.z / b;
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

bool vec3_compare(t_vec3 a, t_vec3 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}
