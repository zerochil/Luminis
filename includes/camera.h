#ifndef CAMERA_H
# define CAMERA_H

# include <scene.h>
# include <vec3.h>
# include <matrix.h>

t_matrix camera_matrix(t_camera camera);
void	camera_rotate(t_camera *camera, void (*rotate)(t_vec3 *, double), double angle);

#endif