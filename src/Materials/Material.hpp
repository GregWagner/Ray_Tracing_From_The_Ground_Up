#pragma once

#include "RGBColor.hpp"
#include "ShadeRec.hpp"
#include "World.hpp"

class Material {
    public:
    Material();

    Material(const Material& material);

    Material(Material&& material) = default;

    [[nodiscard]] virtual Material* clone() const = 0;

    virtual ~Material();

    [[nodiscard]] virtual RGBColor shade(ShadeRec& srec);

    protected:
    Material& operator=(const Material& rhs);

    Material& operator=(Material&& rhs) = default;
};
