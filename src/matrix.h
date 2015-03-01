#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <array>
#include "vec3.h"

template <std::size_t R, std::size_t C>
class Matrix;

template <std::size_t R, std::size_t C>
std::ostream& operator <<(
		std::ostream& s,
		const Matrix<R,C>& m
	)
{
	s << "Matrix (" << R << "x" << C << ")" << std::endl;
	for(std::size_t x = 0; x < R; x++)
	{
		for(std::size_t y = 0; y < C; y++)
		{
			s << m[x][y];
			if (y < C - 1)
			{
				s << "\t";
			}
		}
		s << "\n";
	}
	return s;
}

template <std::size_t R, std::size_t C>
class Matrix
{
private:
	//const int rows, cols;
	std::array<std::array<float,C>,R> m;
public:
	Matrix() : m(std::array<std::array<float,C>,R>()) { }

	inline std::array<float,C>& operator[](const int i)
	{
		return m[i];
	}

	const std::array<float,C> operator[](const int i) const
	{
		return m[i];
	}

	template<std::size_t N>
	Matrix<R,N> operator *(const Matrix<C,N> a) const
	{
		Matrix<R,N> result = Matrix<R,N>();
		for(std::size_t x = 0; x < R; x++)
		{
			for(std::size_t y = 0; y < N; y++)
			{
				for(std::size_t i = 0; i < C; i++)
				{
					result[x][y] += m[x][i] * a[i][y];
				}
			}
		}
		return result;
	}
	//Matrix transpose();
	//Matrix inverse();

	friend std::ostream& operator << <> (std::ostream& s, const Matrix& m);
};

template <std::size_t S>
Matrix<S,S> identity()
{
	Matrix<S,S> matrix = Matrix<S,S>();

	for(std::size_t x = 0; x < S; x++)
	{
		for(std::size_t y = 0; y < S; y++)
		{
			if (x == y)
			{
				matrix[x][y] = 1.f;
			}
		}
	}

	return matrix;
}

Vec3f m2v(const Matrix<4,1> m);

Matrix<4,1> v2m(const Vec3f v);

Matrix<4,4> move_by(const Vec3f v);

Matrix<4,4> scale_by(const Vec3f v);

Matrix<4,4> rotate_by_x(float a);

Matrix<4,4> rotate_by_y(float a);

Matrix<4,4> rotate_by_z(float a);

#endif // __MATRIX_H__
