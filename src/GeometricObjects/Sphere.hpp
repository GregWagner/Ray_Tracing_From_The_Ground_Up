#ifndef __SPHERE__
#define __SPHERE__

#include "GeometricObject.hpp"

class Sphere : public GeometricObject {
    public:
    Sphere();

    Sphere(Point3D center, double r);

    Sphere(const Sphere& sphere);

    [[nodiscard]] Sphere* clone() const override;

    ~Sphere() override;

    Sphere& operator=(const Sphere& sphere);

    void set_center(const Point3D& c);

    void set_center(const double x, const double y, const double z);

    void set_radius(const double r);

    [[nodiscard]] bool hit(const Ray& ray, double& t,
                           ShadeRec& s) const override;

    private:
    Point3D center; // center coordinates as a point
    double radius;  // the radius

    static const double kEpsilon; // for shadows and secondary rays
};

inline void Sphere::set_center(const Point3D& c) {
    center = c;
}

inline void Sphere::set_center(const double x, const double y, const double z) {
    center.x = x;
    center.y = y;
    center.z = z;
}

inline void Sphere::set_radius(const double r) {
    radius = r;
}

#endif
