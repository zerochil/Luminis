#include <camera.h>

t_matrix camera_matrix(t_camera camera)
{
	t_matrix matrix;

	matrix = matrix_identity();

	matrix.data[0] = camera.right.x;
	matrix.data[1] = camera.up.x;
	matrix.data[2] = -camera.forward.x;
	matrix.data[3] = camera.origin.x;

	matrix.data[4] = camera.right.y;
	matrix.data[5] = camera.up.y;
	matrix.data[6] = -camera.forward.y;
	matrix.data[7] = camera.origin.y;
	
	matrix.data[8] = camera.right.z;
	matrix.data[9] = camera.up.z;
	matrix.data[10] = -camera.forward.z;
	matrix.data[11] = camera.origin.z;
	return (matrix);
}

void	camera_rotate(t_camera *camera, void (*rotate)(t_vec3 *, double), double angle)
{
	rotate(&camera->forward, angle);
	camera->forward = vec3_normalize(camera->forward);
	rotate(&camera->up, angle);
	camera->up = vec3_normalize(camera->up);
	rotate(&camera->right, angle);
	camera->right = vec3_normalize(camera->right);
}
