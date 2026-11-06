#include "Directional.hpp"

// ---------------------------------------------------------------------- default constructor

Directional::Directional()
	: Light(),
	  ls(1.0),
	  color(1.0),
	  dir(0, 1, 0) {}


// ---------------------------------------------------------------------- dopy constructor

Directional::Directional(const Directional& dl)
	: Light(dl),
	  ls(dl.ls),
	  color(dl.color),
	  dir(dl.dir) {}


// ---------------------------------------------------------------------- clone

Light*
Directional::clone() const {
	return (new Directional(*this));
}


// ---------------------------------------------------------------------- assignment operator

Directional&
Directional::operator=(const Directional& rhs) {
	if (this == &rhs)
		return (*this);

	Light::operator=(rhs);

	ls = rhs.ls;
	color = rhs.color;
	dir = rhs.dir;

	return (*this);
}


// ---------------------------------------------------------------------- destructor

Directional::~Directional() {}


// ---------------------------------------------------------------------- get_direction
// as this function is virtual, it shouldn't be inlined

Vector3D
Directional::get_direction(ShadeRec& sr [[maybe_unused]]) {
	return (dir);
}

// ------------------------------------------------------------------------------  L

RGBColor
Directional::L(ShadeRec& s [[maybe_unused]]) {
	return (ls * color);
}
