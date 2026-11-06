#include "Material.hpp"

Material::Material() {}

Material::Material(const Material &m [[maybe_unused]]) {}

Material &Material::operator=(const Material &rhs) {
  if (this == &rhs) {
    return (*this);
}

  return (*this);
}

Material::~Material() {}

RGBColor Material::shade(ShadeRec &sr [[maybe_unused]]) { return (black); }
