#include <debug.h>

void print_vec3(t_vec3 vec, char *name)
{
	printf("\t%s {%.2f, %.2f, %.2f}\n", name, vec.x, vec.y, vec.z);
}

void print_color(t_color color)
{
	printf("\tcolor {%f, %f, %f}\n", color.r, color.g, color.b);
}

void	print_scene(t_scene *scene)
{
	printf("Ambient:\n");
	printf("\tintensity: %.2f\n", scene->ambient.intensity);
	print_color(scene->ambient.color);
	printf("\n");
	printf("Camera:\n");
	print_vec3(scene->camera.origin, "origin");
	print_vec3(scene->camera.forward, "forward");
	print_vec3(scene->camera.up, "up");
	print_vec3(scene->camera.right, "right");
	printf("\tfov: %.2f\n", scene->camera.fov);
	for (size_t i = 0; i < scene->lights->size; i++)
	{
		t_light *light = scene->lights->data[i];
		printf("Light %zu:\n", i);
		print_vec3(light->origin, "origin");
		printf("\tintensity: %.2f\n", light->intensity);
		print_color(light->color);
	}
	for (size_t i = 0; i < scene->objects->size; i++)
	{
		t_object *object;
		object = scene->objects->data[i];
		printf("Object %zu:\n", i);
		switch (object->type)
		{
			case SPHERE:
				printf("\ttype: SPHERE\n");
				printf("\tradius: %.2f\n", object->radius);
				break;
			case PLANE:
				printf("\ttype: PLANE\n");
				print_vec3(object->orientation, "orientation");
				break;
			case CYLINDER:
				printf("\ttype: CYLINDER\n");
				print_vec3(object->orientation, "orientation");
				printf("\tradius: %.2f\n", object->radius);
				printf("\theight: %.2f\n", object->height);
				break;
			case CONE:
				printf("\ttype: CONE\n");
				print_vec3(object->orientation, "orientation");
				printf("\thalf-angle: %.2f\n", object->angle);
				break;
		}
		print_color(object->color);
		print_vec3(object->origin, "origin");
	}
}
