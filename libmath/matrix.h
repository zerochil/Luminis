#ifndef MATRIX_H
#define MATRIX_H

#include "vec3.h"

typedef struct s_matrix {
	double data[16];
} matrix;

matrix matrix_identity();
matrix matrix_translate(double x, double y, double z);
matrix matrix_multiply(matrix a, matrix b);


#endif
