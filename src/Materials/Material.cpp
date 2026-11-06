#include "Material.hpp"

// ---------------------------------------------------------------- default constructor

Material::Material() {}


// ---------------------------------------------------------------- copy constructor

Material::Material(const Material& m [[maybe_unused]]) {}


// ---------------------------------------------------------------- assignment operator

Material&
Material::operator=(const Material& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------- destructor

Material::~Material() {}


// ---------------------------------------------------------------- shade

RGBColor
Material::shade(ShadeRec& sr [[maybe_unused]]) {
	return (black);
}
