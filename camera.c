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
	camera->right = vec3_cross(camera->forward, (t_vec3){0, 1, 0});
	camera->right = vec3_normalize(camera->right);
	camera->up = vec3_cross(camera->right, camera->forward);
	camera->up = vec3_normalize(camera->up);
}

void camera_translate(t_camera *camera, int direction, double step)
{
	double aspect_ratio = (double)WIDTH / HEIGHT;
	double scale = tan((camera->fov * M_PI / 180.0) / 2.0);
	int x = WIDTH / 2;
	int y = HEIGHT / 2;
	double x_ndc = (x + 0.5) / WIDTH;
	double y_ndc = (y + 0.5) / HEIGHT;
	double x_screen = (2 * x_ndc - 1) * aspect_ratio * scale;
	double y_screen = (1 - 2 * y_ndc) * scale;
	t_matrix view_matrix = camera_matrix(*camera);
	t_vec3 dir;
	if (direction == FORWARD)
		dir = vec3_mul_matrix((t_vec3){x_screen, y_screen, -1}, view_matrix);
	else if (direction == UP)
		dir = vec3_mul_matrix((t_vec3){x_screen, -1, y_screen}, view_matrix);
	else
		dir = vec3_mul_matrix((t_vec3){1, x_screen, y_screen}, view_matrix);
	camera->origin = vec3_add(camera->origin, vec3_mul_scalar(dir, step));	
}