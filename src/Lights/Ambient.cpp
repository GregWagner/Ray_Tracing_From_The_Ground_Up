
#include "Ambient.hpp"

// ---------------------------------------------------------------------- default constructor

Ambient::Ambient()
	: Light(),
	  ls(1.0),
	  color(1.0) {}


// ---------------------------------------------------------------------- copy constructor

Ambient::Ambient(const Ambient& a)
	: Light(a),
	  ls(a.ls),
	  color(a.color) {}


// ---------------------------------------------------------------------- clone

Light*
Ambient::clone() const {
	return (new Ambient(*this));
}


// ---------------------------------------------------------------------- assignment operator

Ambient&
Ambient::operator=(const Ambient& rhs) {
	if (this == &rhs)
		return (*this);

	Light::operator=(rhs);

	ls = rhs.ls;
	color = rhs.color;

	return (*this);
}


// ---------------------------------------------------------------------- destructor

Ambient::~Ambient() {}


// ---------------------------------------------------------------------- get_direction

Vector3D
Ambient::get_direction(ShadeRec& s [[maybe_unused]]) {
	return (Vector3D(0.0));
}


// ---------------------------------------------------------------------- L

RGBColor
Ambient::L(ShadeRec& sr [[maybe_unused]]) {
	return (ls * color);
}
