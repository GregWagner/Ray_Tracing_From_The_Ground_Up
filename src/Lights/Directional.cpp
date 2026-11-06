#include "Directional.hpp"

Directional::Directional() : Light(), ls(1.0), color(1.0), dir(0, 1, 0) {}

Directional::Directional(const Directional& dl) = default;

Light* Directional::clone() const {
    return (new Directional(*this));
}

Directional& Directional::operator=(const Directional& rhs) {
    if (this == &rhs) {
        return (*this);
    }

    Light::operator=(rhs);

    ls = rhs.ls;
    color = rhs.color;
    dir = rhs.dir;

    return (*this);
}

Directional::~Directional() = default;

// as this function is virtual, it shouldn't be inlined
Vector3D Directional::get_direction(ShadeRec& sr [[maybe_unused]]) {
    return (dir);
}

RGBColor Directional::L(ShadeRec& s [[maybe_unused]]) {
    return (ls * color);
}
