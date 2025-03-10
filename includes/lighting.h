#ifndef LIGHTING_H
#define LIGHTING_H

#include <libmath.h>
#include <material.h>
#include <scene.h>

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

t_color brdfs(t_vec3 N, t_vec3 V, t_vec3 L, t_material mat);

#endif
