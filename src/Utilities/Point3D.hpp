#ifndef __POINT3D__
#define __POINT3D__

#include "Matrix.hpp"
#include "Vector3D.hpp"

class Point3D {
    public:
    double x, y, z;

    Point3D();
    explicit Point3D(const double a);
    Point3D(const double a, const double b, const double c);
    Point3D(const Point3D& p);
    ~Point3D();

    Point3D& operator=(const Point3D& p);

    Point3D // unary minus
    operator-() const;

    Vector3D // vector joining two points
    operator-(const Point3D& p) const;

    Point3D // addition of a vector
    operator+(const Vector3D& v) const;

    Point3D // subtraction of a vector
    operator-(const Vector3D& v) const;

    Point3D // multiplication by a double on the right
    operator*(const double a) const;

    [[nodiscard]] double // square of distance bertween two points
    d_squared(const Point3D& p) const;

    [[nodiscard]] double // distance bewteen two points
    distance(const Point3D& p) const;
};

// inlined member functions

// unary minus
inline Point3D Point3D::operator-() const {
    return (Point3D(-x, -y, -z));
}

// the vector that joins two points
inline Vector3D Point3D::operator-(const Point3D& p) const {
    return (Vector3D(x - p.x, y - p.y, z - p.z));
}

// addition of a vector to a point that returns a new point
inline Point3D Point3D::operator+(const Vector3D& v) const {
    return (Point3D(x + v.x, y + v.y, z + v.z));
}

// subtraction of a vector from a point that returns a new point
inline Point3D Point3D::operator-(const Vector3D& v) const {
    return (Point3D(x - v.x, y - v.y, z - v.z));
}

// mutliplication by a double on the right
inline Point3D Point3D::operator*(const double a) const {
    return (Point3D(x * a, y * a, z * a));
}

// the square of the distance between the two points as a member function
inline double Point3D::d_squared(const Point3D& p) const {
    return ((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) +
            (z - p.z) * (z - p.z));
}

// inlined non-member function

// multiplication by a double on the left
Point3D operator*(double a, const Point3D& p);

inline Point3D operator*(double a, const Point3D& p) {
    return (Point3D(a * p.x, a * p.y, a * p.z));
}

// non-inlined non-member function

// multiplication by a matrix on the left
Point3D operator*(const Matrix& mat, const Point3D& p);

#endif
