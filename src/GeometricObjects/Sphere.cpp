#include "Sphere.hpp"
#include <cmath>

const double Sphere::kEpsilon = 0.001;

Sphere::Sphere() : GeometricObject(), center(0.0), radius(1.0) {}

Sphere::Sphere(Point3D c, double r) : GeometricObject(), center(c), radius(r) {}

Sphere* Sphere::clone() const {
    return (new Sphere(*this));
}

// copy
Sphere::Sphere(const Sphere& sphere)
    : GeometricObject(sphere), center(sphere.center), radius(sphere.radius) {}

Sphere& Sphere::operator=(const Sphere& rhs) {
    if (this == &rhs) {
        return (*this);
    }

    GeometricObject::operator=(rhs);

    center = rhs.center;
    radius = rhs.radius;

    return (*this);
}

Sphere::~Sphere() {}

bool Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    double t;
    if (radius <= 0.0) {
        return (false);
    }

    Vector3D const temp = ray.o - center;
    double const a = ray.d * ray.d;
    if (a <= 0.0) {
        return (false);
    }
    double const b = 2.0 * temp * ray.d;
    double const c = temp * temp - radius * radius;
    double const disc = b * b - 4.0 * a * c;

    if (disc < 0.0) {
        return (false);
    } else {
        double const e = std::sqrt(disc);
        double const denom = 2.0 * a;
        t = (-b - e) / denom; // smaller root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return (true);
        }

        t = (-b + e) / denom; // larger root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return (true);
        }
    }

    return (false);
}
