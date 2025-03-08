#include <camera.h>
#include <debug.h>


t_matrix camera_matrix(t_camera camera)
{
    t_matrix matrix = matrix_identity();

    matrix.data[0]  = camera.right.x;
    matrix.data[1]  = camera.right.y;
    matrix.data[2]  = camera.right.z;
    matrix.data[3]  = -vec3_dot(camera.right, camera.origin);

    matrix.data[4]  = camera.up.x;
    matrix.data[5]  = camera.up.y;
    matrix.data[6]  = camera.up.z;
    matrix.data[7]  = -vec3_dot(camera.up, camera.origin);

    matrix.data[8]  = -camera.forward.x;
    matrix.data[9]  = -camera.forward.y;
    matrix.data[10] = -camera.forward.z;
    matrix.data[11] = vec3_dot(camera.forward, camera.origin);

    return matrix;
}

void	camera_rotate(t_camera *camera, t_vec3 axis, double angle)
{
    rotate_dev(&camera->forward, axis, angle);
    rotate_dev(&camera->up, axis, angle);
	camera->right = vec3_normalize(vec3_cross(camera->forward, camera->up));
}

void camera_translate(t_camera *camera, int direction, double step)
{
	t_vec3 dir;
	if (direction == Z_POS)
		dir = camera->forward;
	else if (direction == Y_POS)
		dir = camera->up;
	else
		dir = camera->right;
	camera->origin = vec3_add(camera->origin, vec3_mul_scalar(dir, step));	
}