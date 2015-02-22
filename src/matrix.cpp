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

std::vector<float>& Matrix::operator[](const int i)
{
	return m[i];
}
