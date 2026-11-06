#pragma once

#include "GeometricObject.hpp"

class Plane : public GeometricObject {
    public:
    Plane();

    Plane(const Point3D& point, const Normal& normal);

    Plane(const Plane& plane);

    [[nodiscard]] Plane* clone() const override;

    Plane& operator=(const Plane& rhs);

    ~Plane() override;

    [[nodiscard]] bool hit(const Ray& ray, double& tmin,
                           ShadeRec& sr) const override;

    private:
    Point3D a; // point through which plane passes
    Normal n;  // normal to the plane

    static const double kEpsilon; // for shadows and secondary rays
};