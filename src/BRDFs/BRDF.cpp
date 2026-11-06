// This file contians the definition of the class BRDF


#include "Constants.hpp"
#include "BRDF.hpp"

// ---------------------------------------------------------- default constructor

BRDF::BRDF(void) {}


BRDF::BRDF(const BRDF& brdf [[maybe_unused]]) {}


// --------------------------------------------------------------- assignment operator

BRDF& BRDF::operator=(const BRDF& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------- destructor

BRDF::~BRDF(void) {}


// ------------------------------------------------------------------------ f

RGBColor
BRDF::f(const ShadeRec& sr [[maybe_unused]], const Vector3D& wo [[maybe_unused]], const Vector3D& wi [[maybe_unused]]) const {
	return (black);
}


// ------------------------------------------------------------------------ sample_f

RGBColor
BRDF::sample_f(const ShadeRec& sr [[maybe_unused]], const Vector3D& wo [[maybe_unused]], Vector3D& wi [[maybe_unused]]) const {
	return (black);
}


// ------------------------------------------------------------------------ sample_f

RGBColor
BRDF::sample_f(const ShadeRec& sr [[maybe_unused]], const Vector3D& wo [[maybe_unused]], Vector3D& wi [[maybe_unused]], float& pdf [[maybe_unused]]) const {
	return (black);
}


// ------------------------------------------------------------------------ rho

RGBColor
BRDF::rho(const ShadeRec& sr [[maybe_unused]], const Vector3D& wo [[maybe_unused]]) const {
	return (black);
}
