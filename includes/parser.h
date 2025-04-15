/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:53:12 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 15:53:19 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "scene.h"
# include "float.h"
# include <stdbool.h>

bool	parser_error(char *error);

bool	parse_scene(t_scene *scene, char *filename);

bool	parse_float(double *value, char *str);
bool	parse_vec3(t_vec3 *vec, char *str);
bool	parse_color(t_vec3 *color, char *str);
bool	parse_string(char **dest, char *str);

bool	is_normalized(t_vec3 vec);
bool	in_interval(double value, double min, double max);

bool	post_parse(t_scene *scene);
#endif
