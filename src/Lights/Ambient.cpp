
#include "Ambient.hpp"

Ambient::Ambient() : Light(), ls(1.0), color(1.0) {}

Ambient::Ambient(const Ambient& ambient_light)
    : Light(ambient_light), ls(ambient_light.ls), color(ambient_light.color) {}

Light* Ambient::clone() const {
    return (new Ambient(*this));
}

Ambient& Ambient::operator=(const Ambient& rhs) {
    if (this == &rhs) {
        return (*this);
    }

    Light::operator=(rhs);

    ls = rhs.ls;
    color = rhs.color;

    return (*this);
}

Ambient::~Ambient() {}

Vector3D Ambient::get_direction(ShadeRec& srec [[maybe_unused]]) {
    return (Vector3D(0.0));
}

RGBColor Ambient::L(ShadeRec& srec [[maybe_unused]]) {
    return (ls * color);
}
