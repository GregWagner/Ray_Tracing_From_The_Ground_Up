#include "Material.hpp"

Material::Material() = default;

Material::Material(const Material& m [[maybe_unused]]) = default;

Material& Material::operator=(const Material& rhs) {
    if (this == &rhs) {
        return (*this);
    }

    return (*this);
}

Material::~Material() = default;

RGBColor Material::shade(ShadeRec& sr [[maybe_unused]]) {
    return (black);
}
