#ifndef LIGHTING_H
#define LIGHTING_H

#include <libmath.h>
#include <material.h>

struct s_dot_products
{
	double NdotH;
	double NdotV;
	double NdotL;
	double VdotH;
};

struct s_brdf_terms
{
	double d;
	double g;
	double f;
};


#endif
