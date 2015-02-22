#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>

class Matrix
{
private:
	const int rows, cols;
	std::vector<std::vector<float> > m;
public:
	Matrix(int r, int c);
	int nrows() const;
	int ncols() const;

	static Matrix identity(int dimensions);

	std::vector<float>& operator[](const int i);
};

#endif // __MATRIX_H__
