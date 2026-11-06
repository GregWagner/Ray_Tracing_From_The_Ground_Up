#include "Lambertian.hpp"
#include "Constants.hpp"

// ---------------------------------------------------------------------- default constructor

Lambertian::Lambertian(void)
	: BRDF(),
	  kd(0.0),
	  cd(0.0) {}


// ---------------------------------------------------------------------- copy constructor

Lambertian::Lambertian(const Lambertian& lamb)
	: BRDF(lamb),
	  kd(lamb.kd),
	  cd(lamb.cd) {}


// ---------------------------------------------------------------------- clone

Lambertian*
Lambertian::clone(void) const {
	return (new Lambertian(*this));
}


// ---------------------------------------------------------------------- destructor

Lambertian::~Lambertian(void) {}


// ---------------------------------------------------------------------- assignment operator

Lambertian&
Lambertian::operator=(const Lambertian& rhs) {
	if (this == &rhs)
		return (*this);

	BRDF::operator=(rhs);

	kd = rhs.kd;
	cd = rhs.cd;

	return (*this);
}


// ---------------------------------------------------------------------- f

RGBColor
Lambertian::f(const ShadeRec& sr [[maybe_unused]], const Vector3D& wo [[maybe_unused]], const Vector3D& wi [[maybe_unused]]) const {
	return (kd * cd * invPI);
}


// ---------------------------------------------------------------------- rho

RGBColor
Lambertian::rho(const ShadeRec& sr [[maybe_unused]], const Vector3D& wo [[maybe_unused]]) const {
	return (kd * cd);
}
