#include <material.h>

static t_vec3 calculate_f0(t_vec3 albedo, double ior)
{
	return (t_vec3){0,0,0};
}

t_material material_default(t_vec3 color)
{
	t_material material;

	material.name = "default";
	material.albedo = color;
	material.roughness = 0.0;
	material.ior = 1.0;
	material.metallic = 0.0;
	material.f0 = calculate_f0(color, 1.0);
	return (material);
}
