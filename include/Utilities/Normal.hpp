
#ifndef __NORMAL__
#define __NORMAL__

#include "Matrix.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"

class Normal {
	public:
	double x, y, z;

	Normal();
	explicit Normal(double a);
	Normal(double _x, double _y, double _z);
	Normal(const Normal& n);
	explicit Normal(const Vector3D& v); // constructs a normal from vector

	~Normal();

	Normal& operator=(const Normal& rhs);

	Normal& // assignment of a vector to a normal
	operator=(const Vector3D& rhs);

	Normal& // assignment of a point to a normal
	operator=(const Point3D& rhs);

	Normal // unary minus
	operator-() const;

	Normal // addition
	operator+(const Normal& n) const;

	Normal& // compound addition
	operator+=(const Normal& n);

	double
	operator*(const Vector3D& v) const; // dot product with a vector on the right

	Normal // multiplication by a double on the right
	operator*(const double a) const;

	void // convert normal to a unit normal
	normalize();
};

// inlined member functions

// unary minus
inline Normal Normal::operator-() const {
	return (Normal(-x, -y, -z));
}

// addition of two normals
inline Normal Normal::operator+(const Normal& n) const {
	return (Normal(x + n.x, y + n.y, z + n.z));
}

// compound addition of two normals
inline Normal& Normal::operator+=(const Normal& n) {
	x += n.x;
	y += n.y;
	z += n.z;
	return (*this);
}

// dot product of a normal on the left and a vector on the right
inline double Normal::operator*(const Vector3D& v) const {
	return (x * v.x + y * v.y + z * v.z);
}

// multiplication by a double on the right

inline Normal Normal::operator*(const double a) const {
	return (Normal(x * a, y * a, z * a));
}

// inlined non-member functions

// multiplication by a double on the left
Normal operator*(const double a, const Normal& n);

inline Normal operator*(const double f, const Normal& n) {
	return (Normal(f * n.x, f * n.y, f * n.z));
}

// addition of a vector on the left to return a vector
Vector3D operator+(const Vector3D& v, const Normal& n);

inline Vector3D operator+(const Vector3D& v, const Normal& n) {
	return (Vector3D(v.x + n.x, v.y + n.y, v.z + n.z));
}

// subtraction of a normal from a vector to return a vector
Vector3D operator-(const Vector3D&, const Normal& n);

inline Vector3D operator-(const Vector3D& v, const Normal& n) {
	return (Vector3D(v.x - n.x, v.y - n.y, v.z - n.z));
}

// dot product of a vector on the left and a normal on the right
double operator*(const Vector3D& v, const Normal& n);

inline double operator*(const Vector3D& v, const Normal& n) {
	return (v.x * n.x + v.y * n.y + v.z * n.z);
}

// non-inlined non-member function

// multiplication by a matrix on the left
Normal operator*(const Matrix& mat, const Normal& n);

#endif
