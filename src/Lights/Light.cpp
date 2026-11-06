#include "Light.hpp"

#include "Constants.hpp"

// ---------------------------------------------------------------------- default constructor

Light::Light(void) {}

// ---------------------------------------------------------------------- dopy constructor

Light::Light(const Light& ls [[maybe_unused]]) {}


// ---------------------------------------------------------------------- assignment operator

Light&
Light::operator=(const Light& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------------- destructor

Light::~Light(void) {}


// ---------------------------------------------------------------------- L
// returns the radiance

RGBColor
Light::L(ShadeRec& s [[maybe_unused]]) {
	return (black);
}
