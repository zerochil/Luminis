#include <parser.h>

bool is_normalized(t_vec3 vec)
{
	printf("%f\n", vec3_length(vec));
	/*return (vec3_length(vec) > 0.90 && vec3_length(vec) < 1.001);*/
	return (true);
}

bool in_interval(double value, double min, double max)
{
	return (value >= min && value <= max);
}
