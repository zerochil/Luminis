#ifndef MATERIAL_H
# define MATERIAL_H

# include <libmath.h>

typedef struct s_material
{
	char	*name;
	t_vec3	albedo;
	double	roughness;
	double	ior;
	double	metallic;
	t_vec3	f0;
}			t_material;

#endif
