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

void	rotate_dev(t_vec3 *vec, t_vec3 axis, double angle)
{
	angle = angle * (M_PI / 180);
	double half_theta = sin(angle / 2);
	double qx = axis.x * half_theta;
	double qy = axis.y * half_theta;
	double qz = axis.z * half_theta;
	double qw = cos(angle / 2);

	//p' = q * p * conj(q);
	double x = (1 - 2 * qy * qy - 2 * qz * qz) * vec->x;
	x += (2 * qx * qy - 2 * qw * qz) * vec->y;
	x += (2 * qx * qz + 2 * qw * qy) * vec->z;

	double y = (2 * qx * qy + 2 * qw * qz) * vec->x;
	y += (1 - 2 * qx * qx - 2 * qz * qz) * vec->y;
	y += (2 * qy * qz - 2 * qw * qx) * vec->z;

	double z = (2 * qx * qz - 2 * qw * qy) * vec->x;
	z += (2 * qy * qz + 2 * qw * qx) * vec->y;
	z += (1 - 2 * qx * qx - 2 * qy * qy) * vec->z;

	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void	camera_rotate(t_camera *camera, t_vec3 axis, double angle)
{
    rotate_dev(&camera->forward, axis, angle);
    rotate_dev(&camera->up, axis, angle);
	camera->right = vec3_normalize(vec3_cross(camera->forward, camera->up));
	
// 	rotate_dev(&camera->forward, axis, angle);
// 	camera->forward = vec3_normalize(camera->forward);
// 	rotate_dev(&camera->up, axis, angle);
// 	camera->up = vec3_normalize(camera->up);
// 	rotate_dev(&camera->right, axis, angle);
// 	camera->right = vec3_normalize(camera->right);
}

void camera_translate(t_camera *camera, int direction, double step)
{
	t_vec3 dir;
	if (direction == FORWARD)
		dir = camera->forward;
	else if (direction == UP)
		dir = camera->up;
	else
		dir = camera->right;
	camera->origin = vec3_add(camera->origin, vec3_mul_scalar(dir, step));	
}