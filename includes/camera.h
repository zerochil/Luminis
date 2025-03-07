#ifndef CAMERA_H
# define CAMERA_H

# include <scene.h>
# include <vec3.h>
# include <matrix.h>

enum
{
	FORWARD,
	UP,
	RIGHT,
};

t_matrix camera_matrix(t_camera camera);
void	camera_rotate(t_camera *camera, t_vec3 axis, double angle);
void	camera_translate(t_camera *camera, int direction, double step);

#endif