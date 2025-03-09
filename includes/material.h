#ifndef MATERIAL_H
# define MATERIAL_H

# include "color.h"

typedef struct
{
	char	*name;
	t_color	albedo;
	double	roughness;
	double	ior;
	double	metallic;
}			Material;

#endif
