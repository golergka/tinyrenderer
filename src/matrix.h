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
	std::vector<float> operator[](const int i) const;
	Matrix operator*(const Matrix a) const;
	Matrix transpose();
	Matrix inverse();

	friend std::ostream& operator <<(std::ostream& s, const Matrix& m);
};

#endif // __MATRIX_H__
