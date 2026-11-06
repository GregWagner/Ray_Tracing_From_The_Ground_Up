// This file contains the definition of the class RGBColor

#include <cmath>

#include "RGBColor.hpp"

// -------------------------------------------------------- default constructor

RGBColor::RGBColor() : r(0.0), g(0.0), b(0.0) {}

// -------------------------------------------------------- constructor

RGBColor::RGBColor(float c) : r(c), g(c), b(c) {}

// -------------------------------------------------------- constructor

RGBColor::RGBColor(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}

// -------------------------------------------------------- copy constructor

RGBColor::RGBColor(const RGBColor& c) : r(c.r), g(c.g), b(c.b) {}

// -------------------------------------------------------- destructor

RGBColor::~RGBColor() {}

// --------------------------------------------------------assignment operator

RGBColor& RGBColor::operator=(const RGBColor& rhs) {
	if (this == &rhs)
		return (*this);

	r = rhs.r;
	g = rhs.g;
	b = rhs.b;

	return (*this);
}

// -------------------------------------------------------- powc
// raise each component to the specified power
// used for color filtering in Chapter 28

RGBColor RGBColor::powc(float p) const {
	return (RGBColor(std::pow(r, p), std::pow(g, p), std::pow(b, p)));
}
