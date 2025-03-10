#ifndef RAYTRACE_H
#define RAYTRACE_H

#include "scene.h"
#include "material.h"
#include "lighting.h"
#include "camera.h"

t_color raytrace(const t_scene *scene, const t_ray *ray, int depth);

#endif
