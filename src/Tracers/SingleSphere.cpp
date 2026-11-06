#include "SingleSphere.hpp"
#include "ShadeRec.hpp"
#include "World.hpp"

SingleSphere::SingleSphere() : Tracer() {}

SingleSphere::SingleSphere(World *_worldPtr) : Tracer(_worldPtr) {}

SingleSphere::~SingleSphere() {}

RGBColor SingleSphere::trace_ray(const Ray &ray) const {
  ShadeRec sr(*world_ptr); // not used
  double t;                // not used

  if (world_ptr->sphere.hit(ray, t, sr)) {
    return (red);
}
  return (black);
}
