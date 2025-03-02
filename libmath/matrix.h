#ifndef MATRIX_H
#define MATRIX_H

#include "vec3.h"

typedef struct s_matrix {
	double data[16];
} t_matrix;

t_matrix matrix_identity();
t_matrix matrix_translate(t_vec3 v);
t_matrix matrix_multiply(t_matrix a, t_matrix b);
t_matrix matrix_rotate(t_vec3 u, t_vec3 v, t_vec3 w);
t_vec3   matrix_mult_vec3(t_matrix a, t_vec3 b);


#endif
