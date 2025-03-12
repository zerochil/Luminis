#include <parser.h>

bool is_normalized(t_vec3 vec)
{
	return (float_eq(vec3_length(vec), 1));
}

bool in_interval(double value, double min, double max)
{
	return (value >= min && value <= max);
}
