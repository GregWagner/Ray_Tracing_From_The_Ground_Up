#pragma once

#include "RGBColor.hpp"
#include "Vector3D.hpp"

class ShadeRec;

class Light {
    public:
    Light() = default;

    Light(const Light& light_source) = default;

    Light(Light&& light_source) = default;

    Light& operator=(const Light& rhs);

    Light& operator=(Light&& rhs) = default;

    [[nodiscard]] virtual Light* clone() const = 0;

    virtual ~Light() = default;

    [[nodiscard]] virtual Vector3D get_direction(ShadeRec& srec) = 0;

    [[nodiscard]] virtual RGBColor L(ShadeRec& srec);
};