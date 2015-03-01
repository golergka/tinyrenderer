#include <cmath>
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

Matrix<4,4> move_by(const Vec3f v)
{
	Matrix<4,4> result = identity<4>();
	result[0][3] = v.x;
	result[1][3] = v.y;
	result[2][3] = v.z;
	return result;
}

Matrix<4,4> scale_by(const Vec3f v)
{
	Matrix<4,4> result = Matrix<4,4>();
	result[0][0] = v.x;
	result[1][1] = v.y;
	result[2][2] = v.z;
	result[3][3] = 1;
	return result;
}

Matrix<4,4> rotate_by_x(float a)
{
	Matrix<4,4> result = identity<4>();
	result[1][1] =  std::cos(a);
	result[1][2] = -std::sin(a);
	result[2][1] =  std::sin(a);
	result[2][2] =  std::cos(a);
	return result;
}

Matrix<4,4> rotate_by_y(float a)
{
	Matrix<4,4> result = identity<4>();
	result[0][0] =  std::cos(a);
	result[0][2] =  std::sin(a);
	result[2][0] = -std::sin(a);
	result[2][2] =  std::cos(a);
	return result;
}

Matrix<4,4> rotate_by_z(float a)
{
	Matrix<4,4> result = identity<4>();
	result[0][0] =  std::cos(a);
	result[0][1] = -std::sin(a);
	result[1][0] =  std::sin(a);
	result[1][1] =  std::cos(a);
	return result;
}
