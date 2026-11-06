#include "Lambertian.hpp"
#include "Constants.hpp"

Lambertian::Lambertian() : BRDF(), kd(0.0), cd(0.0) {}

Lambertian::Lambertian(const Lambertian &lamb)
    : BRDF(lamb), kd(lamb.kd), cd(lamb.cd) {}

Lambertian *Lambertian::clone() const { return (new Lambertian(*this)); }

Lambertian::~Lambertian() {}

Lambertian &Lambertian::operator=(const Lambertian &rhs) {
  if (this == &rhs)
    return (*this);

  BRDF::operator=(rhs);

  kd = rhs.kd;
  cd = rhs.cd;

  return (*this);
}

RGBColor Lambertian::f(const ShadeRec &sr [[maybe_unused]],
                       const Vector3D &wo [[maybe_unused]],
                       const Vector3D &wi [[maybe_unused]]) const {
  return (kd * cd * invPI);
}

RGBColor Lambertian::rho(const ShadeRec &sr [[maybe_unused]],
                         const Vector3D &wo [[maybe_unused]]) const {
  return (kd * cd);
}
