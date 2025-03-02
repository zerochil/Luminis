#include "matrix.h"

matrix matrix_identity() {
	matrix m;
	for (int i = 0; i < 16; i++) {
		m.data[i] = 0;
	}
	m.data[0] = 1;
	m.data[5] = 1;
	m.data[10] = 1;
	m.data[15] = 1;
	return m;
}

matrix matrix_translate(double x, double y, double z) {
	matrix m = matrix_identity();
	m.data[12] = x;
	m.data[13] = y;
	m.data[14] = z;
	return m;
}


matrix matrix_multiply(matrix a, matrix b) {
	matrix m;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m.data[i * 4 + j] = 0;
			for (int k = 0; k < 4; k++) {
				m.data[i * 4 + j] += a.data[i * 4 + k] * b.data[k * 4 + j];
			}
		}
	}
	return m;
}

t_vec3 matrix_transform(matrix m, t_vec3 v) {
	t_vec3 r;
	r.x = m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z + m.data[3];
	r.y = m.data[4] * v.x + m.data[5] * v.y + m.data[6] * v.z + m.data[7];
	r.z = m.data[8] * v.x + m.data[9] * v.y + m.data[10] * v.z + m.data[11];
	return r;
}
