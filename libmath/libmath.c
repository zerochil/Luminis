#include "libmath.h"

double	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
