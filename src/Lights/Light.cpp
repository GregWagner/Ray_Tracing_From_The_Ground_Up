#include "Light.hpp"

#include "Constants.hpp"

Light::Light() {}

Light::Light(const Light& ls [[maybe_unused]]) {}

Light& Light::operator=(const Light& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	return (*this);
}

Light::~Light() {}

// returns the radiance
RGBColor Light::L(ShadeRec& s [[maybe_unused]]) {
	return (black);
}
