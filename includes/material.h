#ifndef MATERIAL_H
# define MATERIAL_H

# include "color.h"

typedef struct s_material
{
	char	*name;
	t_color	albedo;
	double	roughness;
	double	ior;
	double	metallic;
	double	f0;
}			t_material;

#endif
