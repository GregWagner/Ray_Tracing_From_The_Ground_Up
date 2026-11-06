#pragma once

// Matrix is a 4 x 4 square matrix that is used to represent affine
// transformations we don't need a general m x n matrix

class Matrix {
    public:
    double m[4][4]; // elements

    Matrix();

    Matrix(const Matrix& mat);

    ~Matrix() = default;

    Matrix& operator=(const Matrix& rhs);

    Matrix // multiplication of two matrices
    operator*(const Matrix& mat) const;

    Matrix // division by a double
    operator/(const double d) const;

    void // set to the identity matrix
    set_identity();
};
