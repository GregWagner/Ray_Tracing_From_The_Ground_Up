// This file contains the definition of the class Matrix

#include "Matrix.hpp"

// a default matrix is an identity matrix

Matrix::Matrix() {
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (x == y) {
				m[x][y] = 1.0;
			} else {
				m[x][y] = 0.0;
			}
		}
	}
}

Matrix::Matrix(const Matrix& mat) {
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			m[x][y] = mat.m[x][y];
		}
	}
}

Matrix::~Matrix() {}

Matrix& Matrix::operator=(const Matrix& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			m[x][y] = rhs.m[x][y];
		}
	}

	return (*this);
}

// multiplication of two matrices
Matrix Matrix::operator*(const Matrix& mat) const {
	Matrix product;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			double sum = 0.0;

			for (int j = 0; j < 4; j++) {
				sum += m[x][j] * mat.m[j][y];
			}

			product.m[x][y] = sum;
		}
	}

	return (product);
}

// division by a scalar

Matrix Matrix::operator/(const double d) const {
	Matrix result(*this);

	if (d == 0.0) {
		return (result);
	}

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			result.m[x][y] = m[x][y] / d;
		}
	}

	return (result);
}

// set matrix to the identity matrix

void Matrix::set_identity() {
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (x == y) {
				m[x][y] = 1.0;
			} else {
				m[x][y] = 0.0;
			}
		}
	}
}
