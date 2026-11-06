#include <gtest/gtest.h>

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "RGBColor.hpp"

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