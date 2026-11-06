#include <cmath>

#include <gtest/gtest.h>

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "RGBColor.hpp"
#include "Matrix.hpp"
#include "Normal.hpp"

TEST(Vector3DTest, DefaultConstructor) {
	Vector3D v;
	EXPECT_DOUBLE_EQ(v.x, 0.0);
	EXPECT_DOUBLE_EQ(v.y, 0.0);
	EXPECT_DOUBLE_EQ(v.z, 0.0);
}

TEST(Vector3DTest, Length) {
	Vector3D v(3.0, 4.0, 0.0);
	EXPECT_DOUBLE_EQ(v.length(), 5.0);
}

TEST(Vector3DTest, ConstLength) {
	const Vector3D v(3.0, 4.0, 0.0);
	EXPECT_DOUBLE_EQ(v.length(), 5.0);
	EXPECT_DOUBLE_EQ(v.len_squared(), 25.0);
}

TEST(Point3DTest, Subtraction) {
	Point3D a(1.0, 2.0, 3.0);
	Point3D b(4.0, 5.0, 6.0);
	Vector3D d = b - a;
	EXPECT_DOUBLE_EQ(d.x, 3.0);
	EXPECT_DOUBLE_EQ(d.y, 3.0);
	EXPECT_DOUBLE_EQ(d.z, 3.0);
}

TEST(RGBColorTest, DefaultConstructor) {
	RGBColor c;
	EXPECT_FLOAT_EQ(c.r, 0.0f);
	EXPECT_FLOAT_EQ(c.g, 0.0f);
	EXPECT_FLOAT_EQ(c.b, 0.0f);
}

TEST(RGBColorTest, ScalarConstructor) {
	RGBColor c(0.5f);
	EXPECT_FLOAT_EQ(c.r, 0.5f);
	EXPECT_FLOAT_EQ(c.g, 0.5f);
	EXPECT_FLOAT_EQ(c.b, 0.5f);
}

TEST(RGBColorTest, ComponentConstructor) {
	RGBColor c(0.1f, 0.2f, 0.3f);
	EXPECT_FLOAT_EQ(c.r, 0.1f);
	EXPECT_FLOAT_EQ(c.g, 0.2f);
	EXPECT_FLOAT_EQ(c.b, 0.3f);
}

TEST(RGBColorTest, CopyAndAssignment) {
	RGBColor a(0.1f, 0.2f, 0.3f);
	RGBColor b(a);
	RGBColor c;
	c = a;
	EXPECT_TRUE(b == a);
	EXPECT_TRUE(c == a);
}

TEST(RGBColorTest, Addition) {
	RGBColor a(0.1f, 0.2f, 0.3f);
	RGBColor b(0.4f, 0.5f, 0.6f);
	RGBColor c = a + b;
	EXPECT_FLOAT_EQ(c.r, 0.5f);
	EXPECT_FLOAT_EQ(c.g, 0.7f);
	EXPECT_FLOAT_EQ(c.b, 0.9f);

	a += b;
	EXPECT_FLOAT_EQ(a.r, 0.5f);
	EXPECT_FLOAT_EQ(a.g, 0.7f);
	EXPECT_FLOAT_EQ(a.b, 0.9f);
}

TEST(RGBColorTest, ScalarMultiplication) {
	RGBColor a(0.1f, 0.2f, 0.3f);
	RGBColor b = a * 2.0f;
	RGBColor c = 2.0f * a;
	EXPECT_FLOAT_EQ(b.r, 0.2f);
	EXPECT_FLOAT_EQ(b.g, 0.4f);
	EXPECT_FLOAT_EQ(b.b, 0.6f);
	EXPECT_TRUE(b == c);

	a *= 2.0f;
	EXPECT_TRUE(a == b);
}

TEST(RGBColorTest, Division) {
	RGBColor a(0.2f, 0.4f, 0.6f);
	RGBColor b = a / 2.0f;
	EXPECT_FLOAT_EQ(b.r, 0.1f);
	EXPECT_FLOAT_EQ(b.g, 0.2f);
	EXPECT_FLOAT_EQ(b.b, 0.3f);

	a /= 2.0f;
	EXPECT_TRUE(a == b);
}

TEST(RGBColorTest, ComponentWiseMultiplication) {
	RGBColor a(0.2f, 0.5f, 0.4f);
	RGBColor b(0.5f, 0.2f, 0.25f);
	RGBColor c = a * b;
	EXPECT_FLOAT_EQ(c.r, 0.1f);
	EXPECT_FLOAT_EQ(c.g, 0.1f);
	EXPECT_FLOAT_EQ(c.b, 0.1f);
}

TEST(RGBColorTest, PowcAndAverage) {
	RGBColor a(1.0f, 8.0f, 27.0f);
	RGBColor b = a.powc(1.0f / 3.0f);
	EXPECT_FLOAT_EQ(b.r, 1.0f);
	EXPECT_FLOAT_EQ(b.g, 2.0f);
	EXPECT_FLOAT_EQ(b.b, 3.0f);

	RGBColor c(0.3f, 0.6f, 0.9f);
	EXPECT_NEAR(c.average(), 0.6f, 1e-6);
}

TEST(MatrixTest, DefaultConstructorIsIdentity) {
	Matrix m;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			EXPECT_DOUBLE_EQ(m.m[i][j], (i == j) ? 1.0 : 0.0);
		}
	}
}

TEST(MatrixTest, CopyAndAssignment) {
	Matrix a;
	a.m[0][1] = 2.5;
	a.m[3][2] = -1.25;
	Matrix b(a);
	Matrix c;
	c = a;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			EXPECT_DOUBLE_EQ(b.m[i][j], a.m[i][j]);
			EXPECT_DOUBLE_EQ(c.m[i][j], a.m[i][j]);
		}
	}
}

TEST(MatrixTest, SetIdentity) {
	Matrix m;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m.m[i][j] = 7.0;
		}
	}
	m.set_identity();
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			EXPECT_DOUBLE_EQ(m.m[i][j], (i == j) ? 1.0 : 0.0);
		}
	}
}

TEST(MatrixTest, Multiplication) {
	Matrix a;
	Matrix b;
	a.m[0][0] = 2.0;
	a.m[1][1] = 3.0;
	b.m[0][0] = 4.0;
	b.m[1][1] = 5.0;

	Matrix c = a * b;
	EXPECT_DOUBLE_EQ(c.m[0][0], 8.0);
	EXPECT_DOUBLE_EQ(c.m[1][1], 15.0);
	EXPECT_DOUBLE_EQ(c.m[2][2], 1.0);
	EXPECT_DOUBLE_EQ(c.m[3][3], 1.0);
}

TEST(MatrixTest, MultiplicationIdentity) {
	Matrix a;
	a.m[0][3] = 1.5;
	a.m[1][2] = -2.0;
	Matrix b;
	Matrix c = a * b;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			EXPECT_DOUBLE_EQ(c.m[i][j], a.m[i][j]);
		}
	}
}

TEST(MatrixTest, Division) {
	Matrix a;
	a.m[0][0] = 4.0;
	a.m[1][1] = 6.0;
	Matrix b = a / 2.0;
	EXPECT_DOUBLE_EQ(b.m[0][0], 2.0);
	EXPECT_DOUBLE_EQ(b.m[1][1], 3.0);
	EXPECT_DOUBLE_EQ(a.m[0][0], 4.0);
	EXPECT_DOUBLE_EQ(a.m[1][1], 6.0);
}

TEST(MatrixTest, TransformPoint) {
	Matrix m;
	m.m[0][3] = 5.0;
	m.m[1][3] = -1.0;
	Point3D p(1.0, 2.0, 3.0);
	Point3D q = m * p;
	EXPECT_DOUBLE_EQ(q.x, 6.0);
	EXPECT_DOUBLE_EQ(q.y, 1.0);
	EXPECT_DOUBLE_EQ(q.z, 3.0);
}

TEST(MatrixTest, TransformVectorIgnoresTranslation) {
	Matrix m;
	m.m[0][3] = 5.0;
	Vector3D v(1.0, 2.0, 3.0);
	Vector3D w = m * v;
	EXPECT_DOUBLE_EQ(w.x, 1.0);
	EXPECT_DOUBLE_EQ(w.y, 2.0);
	EXPECT_DOUBLE_EQ(w.z, 3.0);
}

TEST(NormalTest, Constructors) {
	Normal a;
	EXPECT_DOUBLE_EQ(a.x, 0.0);
	EXPECT_DOUBLE_EQ(a.y, 0.0);
	EXPECT_DOUBLE_EQ(a.z, 0.0);

	Normal b(2.0);
	EXPECT_DOUBLE_EQ(b.x, 2.0);
	EXPECT_DOUBLE_EQ(b.y, 2.0);
	EXPECT_DOUBLE_EQ(b.z, 2.0);

	Normal c(1.0, 2.0, 3.0);
	EXPECT_DOUBLE_EQ(c.x, 1.0);
	EXPECT_DOUBLE_EQ(c.y, 2.0);
	EXPECT_DOUBLE_EQ(c.z, 3.0);

	Normal d(Vector3D(4.0, 5.0, 6.0));
	EXPECT_DOUBLE_EQ(d.x, 4.0);
	EXPECT_DOUBLE_EQ(d.y, 5.0);
	EXPECT_DOUBLE_EQ(d.z, 6.0);
}

TEST(NormalTest, CopyAndAssignment) {
	Normal a(1.0, 2.0, 3.0);
	Normal b(a);
	Normal c;
	c = a;
	EXPECT_DOUBLE_EQ(b.x, a.x);
	EXPECT_DOUBLE_EQ(b.y, a.y);
	EXPECT_DOUBLE_EQ(b.z, a.z);
	EXPECT_DOUBLE_EQ(c.x, a.x);

	Vector3D v(4.0, 5.0, 6.0);
	c = v;
	EXPECT_DOUBLE_EQ(c.x, 4.0);
	EXPECT_DOUBLE_EQ(c.y, 5.0);
	EXPECT_DOUBLE_EQ(c.z, 6.0);

	Point3D p(7.0, 8.0, 9.0);
	c = p;
	EXPECT_DOUBLE_EQ(c.x, 7.0);
	EXPECT_DOUBLE_EQ(c.y, 8.0);
	EXPECT_DOUBLE_EQ(c.z, 9.0);
}

TEST(NormalTest, Arithmetic) {
	Normal a(1.0, 2.0, 3.0);
	Normal b = -a;
	EXPECT_DOUBLE_EQ(b.x, -1.0);
	EXPECT_DOUBLE_EQ(b.y, -2.0);
	EXPECT_DOUBLE_EQ(b.z, -3.0);

	Normal c(1.0, 1.0, 1.0);
	a += c;
	EXPECT_DOUBLE_EQ(a.x, 2.0);
	EXPECT_DOUBLE_EQ(a.y, 3.0);
	EXPECT_DOUBLE_EQ(a.z, 4.0);

	Normal d(1.0, 2.0, 3.0);
	Normal e(4.0, 5.0, 6.0);
	Normal f = d + e;
	EXPECT_DOUBLE_EQ(f.x, 5.0);
	EXPECT_DOUBLE_EQ(f.y, 7.0);
	EXPECT_DOUBLE_EQ(f.z, 9.0);
}

TEST(NormalTest, DotProduct) {
	Normal n(1.0, 2.0, 3.0);
	Vector3D v(4.0, 5.0, 6.0);
	EXPECT_DOUBLE_EQ(n * v, 32.0);
	EXPECT_DOUBLE_EQ(v * n, 32.0);
}

TEST(NormalTest, ScalarMultiplication) {
	Normal n(1.0, 2.0, 3.0);
	Normal a = n * 2.0;
	Normal b = 2.0 * n;
	EXPECT_DOUBLE_EQ(a.x, 2.0);
	EXPECT_DOUBLE_EQ(a.y, 4.0);
	EXPECT_DOUBLE_EQ(a.z, 6.0);
	EXPECT_DOUBLE_EQ(b.x, 2.0);
	EXPECT_DOUBLE_EQ(b.y, 4.0);
	EXPECT_DOUBLE_EQ(b.z, 6.0);
}

TEST(NormalTest, Normalize) {
	Normal n(3.0, 4.0, 0.0);
	n.normalize();
	EXPECT_DOUBLE_EQ(n.x, 3.0 / 5.0);
	EXPECT_DOUBLE_EQ(n.y, 4.0 / 5.0);
	EXPECT_DOUBLE_EQ(n.z, 0.0);

	Normal zero(0.0, 0.0, 0.0);
	zero.normalize();
	EXPECT_DOUBLE_EQ(zero.x, 0.0);
	EXPECT_DOUBLE_EQ(zero.y, 0.0);
	EXPECT_DOUBLE_EQ(zero.z, 0.0);
}

TEST(NormalTest, MixedAddition) {
	Vector3D v(1.0, 2.0, 3.0);
	Normal n(4.0, 5.0, 6.0);
	Vector3D result = v + n;
	EXPECT_DOUBLE_EQ(result.x, 5.0);
	EXPECT_DOUBLE_EQ(result.y, 7.0);
	EXPECT_DOUBLE_EQ(result.z, 9.0);

	Vector3D diff = v - n;
	EXPECT_DOUBLE_EQ(diff.x, -3.0);
	EXPECT_DOUBLE_EQ(diff.y, -3.0);
	EXPECT_DOUBLE_EQ(diff.z, -3.0);
}

TEST(NormalTest, MatrixTransform) {
	Matrix identity;
	Normal n(1.0, 2.0, 3.0);
	Normal result = identity * n;
	EXPECT_DOUBLE_EQ(result.x, n.x);
	EXPECT_DOUBLE_EQ(result.y, n.y);
	EXPECT_DOUBLE_EQ(result.z, n.z);
}