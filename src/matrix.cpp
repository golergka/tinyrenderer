#include <stdexcept>
#include <iostream>
#include "matrix.h"

Matrix::Matrix(int r, int c) : 
	rows(r), 
	cols(c),
	m(std::vector<std::vector<float> >(r, std::vector<float>(c, 0.) ))
{ }

Matrix Matrix::identity(int dimensions)
{
	Matrix m = Matrix(dimensions, dimensions);
	for(int x = 0; x < dimensions; x++)
	{
		for(int y = 0; y < dimensions; y++)
		{
			m[x][y] = x == y ? 1. : 0.;
		}
	}
	return m;
}

int Matrix::ncols() const
{
	return cols;
}

int Matrix::nrows() const
{
	return rows;
}

std::vector<float>& Matrix::operator [](const int i)
{
	return m[i];
}

std::vector<float> Matrix::operator [](const int i) const
{
	return m[i];
}

Matrix Matrix::operator * (const Matrix a) const
{
	if (cols != a.rows)
	{
		throw std::invalid_argument("matrix sizes incompatible for multiplication");
	}
	Matrix r = Matrix(rows, a.cols);
	for(int x = 0; x < r.rows; x++)
	{
		for(int y = 0; y < r.cols; y++)
		{
			for(int i = 0; i < cols; i++)
			{
				r[x][y] += m[x][i] * a.m[i][y];
			}
		}
	}
	return r;
}

std::ostream& operator <<(std::ostream& s, const Matrix& m)
{
	for(int x = 0; x < m.nrows(); x++)
	{
		for(int y = 0; y < m.ncols(); y++)
		{
			s << m[x][y];
			if (y < m.ncols() - 1)
			{
				s << "\t";
			}
		}
		s << "\n";
	}
	return s;
}
