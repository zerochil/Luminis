#include "matrix.h"

t_matrix matrix_identity() {
	t_matrix m;
	for (int i = 0; i < 16; i++) {
		m.data[i] = 0;
	}
	m.data[0] = 1;
	m.data[5] = 1;
	m.data[10] = 1;
	m.data[15] = 1;
	return m;
}

t_matrix matrix_translate(t_vec3 v) {
	t_matrix m;

	m = matrix_identity();
	m.data[3] = v.x;
	m.data[7] = v.y;
	m.data[11] = v.z;
	return m;
}


t_matrix matrix_multiply(t_matrix a, t_matrix b) {
	t_matrix m;
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

t_matrix matrix_rotate(t_vec3 u, t_vec3 v, t_vec3 w)
{
	t_matrix m;

	m = matrix_identity();
	m.data[0] = u.x;
	m.data[1] = u.y;
	m.data[2] = u.z;
	m.data[4] = v.x;
	m.data[5] = v.y;
	m.data[6] = v.z;
	m.data[8] = w.x;
	m.data[9] = w.y;
	m.data[10] = w.z;
	return (m);
}

t_vec3 matrix_transform(t_matrix m, t_vec3 v) {
	t_vec3 r;
	r.x = m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z + m.data[3];
	r.y = m.data[4] * v.x + m.data[5] * v.y + m.data[6] * v.z + m.data[7];
	r.z = m.data[8] * v.x + m.data[9] * v.y + m.data[10] * v.z + m.data[11];
	return r;
}

t_vec3   matrix_mult_vec3(t_matrix a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.data[0] * b.x + a.data[1] * b.y + a.data[2] * b.z + a.data[3];
	result.y = a.data[4] * b.x + a.data[5] * b.y + a.data[6] * b.z + a.data[7];
	result.z = a.data[8] * b.x + a.data[9] * b.y + a.data[10] * b.z + a.data[11];
	return (result);
}

t_matrix matrix_transpose(t_matrix m)
{
	t_matrix result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.data[i * 4 + j] = m.data[j * 4 + i];
		}
	}
	return (result);
}
