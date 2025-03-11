#ifndef _OBJECT_H
# define _OBJECT_H

# include <object.h>

bool intersect_plane(t_object *obj, t_ray *ray, t_hit *hit);
bool intersect_sphere(t_object *obj, t_ray *ray, t_hit *hit);
bool intersect_cylinder(t_object *obj, t_ray *ray, t_hit *hit);
bool intersect_cone(t_object *obj, t_ray *ray, t_hit *hit);

#endif