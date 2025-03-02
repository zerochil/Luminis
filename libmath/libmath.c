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

bool float_eq(double a, double b)
{
    return fabs(a - b) < EPSILON * fmax(fabs(a), fabs(b));
}
