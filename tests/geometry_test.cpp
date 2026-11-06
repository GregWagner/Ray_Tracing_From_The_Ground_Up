#include <gtest/gtest.h>

#include "World.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Ray.hpp"

TEST(SphereTest, HitCenter) {
	World world;
	Sphere sphere(Point3D(0.0, 0.0, 0.0), 1.0);
	Ray ray(Point3D(0.0, 0.0, -5.0), Vector3D(0.0, 0.0, 1.0));
	double t = 0.0;
	ShadeRec sr(world);
	bool hit = sphere.hit(ray, t, sr);
	EXPECT_TRUE(hit);
	EXPECT_NEAR(t, 4.0, 1e-6);
}

TEST(SphereTest, Miss) {
	World world;
	Sphere sphere(Point3D(0.0, 0.0, 0.0), 1.0);
	Ray ray(Point3D(0.0, 5.0, -5.0), Vector3D(0.0, 0.0, 1.0));
	double t = 0.0;
	ShadeRec sr(world);
	bool hit = sphere.hit(ray, t, sr);
	EXPECT_FALSE(hit);
}

TEST(PlaneTest, Hit) {
	World world;
	Plane plane(Point3D(0.0, 0.0, 0.0), Normal(0.0, 0.0, 1.0));
	Ray ray(Point3D(0.0, 0.0, -5.0), Vector3D(0.0, 0.0, 1.0));
	double t = 0.0;
	ShadeRec sr(world);
	bool hit = plane.hit(ray, t, sr);
	EXPECT_TRUE(hit);
	EXPECT_NEAR(t, 5.0, 1e-6);
}