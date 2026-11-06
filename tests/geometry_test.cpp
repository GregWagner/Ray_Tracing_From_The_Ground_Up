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

TEST(SphereTest, TangentRayHits) {
	World world;
	Sphere sphere(Point3D(0.0, 0.0, 0.0), 1.0);
	Ray ray(Point3D(0.0, 1.0, -5.0), Vector3D(0.0, 0.0, 1.0));
	double t = 0.0;
	ShadeRec sr(world);
	bool hit = sphere.hit(ray, t, sr);
	EXPECT_TRUE(hit);
	EXPECT_NEAR(t, 5.0, 1e-6);
}

TEST(SphereTest, RayFromInside) {
	World world;
	Sphere sphere(Point3D(0.0, 0.0, 0.0), 1.0);
	Ray ray(Point3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 1.0));
	double t = 0.0;
	ShadeRec sr(world);
	bool hit = sphere.hit(ray, t, sr);
	EXPECT_TRUE(hit);
	EXPECT_NEAR(t, 1.0, 1e-6);
}

TEST(SphereTest, RayAwayMisses) {
	World world;
	Sphere sphere(Point3D(0.0, 0.0, 0.0), 1.0);
	Ray ray(Point3D(0.0, 0.0, -5.0), Vector3D(0.0, 0.0, -1.0));
	double t = 0.0;
	ShadeRec sr(world);
	bool hit = sphere.hit(ray, t, sr);
	EXPECT_FALSE(hit);
}

TEST(SphereTest, ZeroDirectionMisses) {
	World world;
	Sphere sphere(Point3D(0.0, 0.0, 0.0), 1.0);
	Ray ray(Point3D(0.0, 0.0, -5.0), Vector3D(0.0, 0.0, 0.0));
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

TEST(PlaneTest, MissBehind) {
	World world;
	Plane plane(Point3D(0.0, 0.0, 0.0), Normal(0.0, 0.0, 1.0));
	Ray ray(Point3D(0.0, 0.0, 5.0), Vector3D(0.0, 0.0, 1.0));
	double t = 0.0;
	ShadeRec sr(world);
	bool hit = plane.hit(ray, t, sr);
	EXPECT_FALSE(hit);
}

TEST(PlaneTest, MissParallel) {
	World world;
	Plane plane(Point3D(0.0, 0.0, 0.0), Normal(0.0, 0.0, 1.0));
	Ray ray(Point3D(0.0, 0.0, 5.0), Vector3D(1.0, 0.0, 0.0));
	double t = 0.0;
	ShadeRec sr(world);
	bool hit = plane.hit(ray, t, sr);
	EXPECT_FALSE(hit);
}

TEST(PlaneTest, RayInPlaneMisses) {
	World world;
	Plane plane(Point3D(0.0, 0.0, 0.0), Normal(0.0, 0.0, 1.0));
	Ray ray(Point3D(1.0, 2.0, 0.0), Vector3D(1.0, 0.0, 0.0));
	double t = 0.0;
	ShadeRec sr(world);
	bool hit = plane.hit(ray, t, sr);
	EXPECT_FALSE(hit);
}

TEST(PlaneTest, OffsetPlaneHit) {
	World world;
	Plane plane(Point3D(0.0, 0.0, 2.0), Normal(0.0, 0.0, 1.0));
	Ray ray(Point3D(0.0, 0.0, -5.0), Vector3D(0.0, 0.0, 1.0));
	double t = 0.0;
	ShadeRec sr(world);
	bool hit = plane.hit(ray, t, sr);
	EXPECT_TRUE(hit);
	EXPECT_NEAR(t, 7.0, 1e-6);
}

TEST(WorldTest, HitObjectsChoosesNearest) {
	World world;
	world.add_object(new Sphere(Point3D(0.0, 0.0, 0.0), 1.0));
	world.add_object(new Sphere(Point3D(0.0, 0.0, 10.0), 1.0));

	Ray ray(Point3D(0.0, 0.0, -5.0), Vector3D(0.0, 0.0, 1.0));
	ShadeRec sr = world.hit_objects(ray);
	EXPECT_TRUE(sr.hit_an_object);
	EXPECT_NEAR(sr.t, 4.0, 1e-6);
}

TEST(WorldTest, HitObjectsMiss) {
	World world;
	world.add_object(new Sphere(Point3D(0.0, 0.0, 0.0), 1.0));

	Ray ray(Point3D(0.0, 5.0, -5.0), Vector3D(0.0, 0.0, 1.0));
	ShadeRec sr = world.hit_objects(ray);
	EXPECT_FALSE(sr.hit_an_object);
}