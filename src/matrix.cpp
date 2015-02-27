#include "matrix.h"

Vec3f m2v(const Matrix<4,1> m)
{
	if (0. == m[3][0])
	{
		throw std::overflow_error("last element can't be 0");
	}
	return Vec3f(
			m[0][0] / m[3][0],
			m[1][0] / m[3][0],
			m[2][0] / m[3][0]
		);
}

Matrix<4,1> v2m(const Vec3f v)
{
	Matrix<4,1> m = Matrix<4,1>();
	m[0][0] = v.x;
	m[1][0] = v.y;
	m[2][0] = v.z;
	m[3][0] = 1;
	return m;
}
