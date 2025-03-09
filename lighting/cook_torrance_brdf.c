#include <lighting.h>

static inline double distribution(double NdotH, double roughness)
{
	double alpha_sq;
	double NdotH_sq;
	double denom;

	alpha_sq = roughness * roughness * roughness * roughness;
	NdotH_sq = NdotH * NdotH;
	denom = NdotH_sq * (alpha_sq - 1.0) + 1.0;
	return alpha_sq / (M_PI * denom * denom);
}

static inline double geometry(double NdotV, double roughness)
{
	double k = roughness * roughness / 2.0;
	double denom = NdotV * (1.0 - k) + k;
	return NdotV / denom;
}

double fresnel_schlick(double VdotH, double f0)
{
	return f0 + (1.0 - f0) * pow(1.0 - VdotH, 5);
}

double cook_torrance_brdf(struct s_dot_products dp, struct s_brdf_terms bt)
{
	return bt.d * bt.g * bt.f / (4.0 * dp.NdotV * dp.NdotL);
}

double lambertian_brdf(struct s_brdf_terms bt, struct s_dot_products dp, t_material mat)
{
	return (1.0 - bt.f) * (1.0 - mat.metallic) * dp.NdotL / M_PI;
}

t_color brdf(t_vec3 N, t_vec3 V, t_vec3 L, t_material mat)
{
	t_vec3 H;
	struct s_dot_products dp;
	struct s_brdf_terms bt;

	H = vec3_normalize(vec3_add(V, L));
	dp.NdotH = fmax(vec3_dot(N, H), 0);
	dp.NdotV = fmax(vec3_dot(N, V), 0);
	dp.NdotL = fmax(vec3_dot(N, L), 0);
	dp.VdotH = fmax(vec3_dot(V, H), 0);
	
	bt.d = distribution(dp.NdotH, mat.roughness);
	bt.g = geometry(dp.NdotV, mat.roughness) * geometry(dp.NdotL, mat.roughness);
	bt.f = fresnel_schlick(dp.VdotH, mat.f0);
	
	double specular_intensity = cook_torrance_brdf(dp, bt);
	double diffuse_intensity = lambertian_brdf(bt, dp, mat);

	t_color color = mat.albedo;
	color_mul_scalar(&color, diffuse_intensity);
	t_color specular;
	if (mat.metallic > 0)
		specular = mat.albedo;
	else if (mat.metallic == 0)
		specular = (t_color){1, 1, 1};
	color_mul_scalar(&specular, specular_intensity);
	color_add(&color, &specular);

	return color;
}


// TODO: MULTIPLE LIGHTS
