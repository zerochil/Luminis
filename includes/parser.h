#ifndef PARSER_H
#define PARSER_H

#include "scene.h"
#include "libft.h"
#include "debug.h"
#include <stdbool.h>

bool parser_error(char *error);

bool	parse_scene(t_scene *scene, char *filename);

bool parse_float(double *value, char *str);
bool parse_vec3(t_vec3 *vec, char *str);
bool parse_color(t_color *color, char *str);
bool parse_string(char **dest, char *str);


bool is_normalized(t_vec3 vec);
bool in_interval(double value, double min, double max);

#endif
