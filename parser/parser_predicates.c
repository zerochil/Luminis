#include <parser.h>

bool is_normalized(t_vec3 vec)
{
	return (vec.x >= -1 && vec.x <= 1
		&& vec.y >= -1 && vec.y <= 1
		&& vec.z >= -1 && vec.z <= 1);
}

bool in_interval(float value, float min, float max)
{
	return (value >= min && value <= max);
}
