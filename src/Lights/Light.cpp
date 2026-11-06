#include "Light.hpp"

#include "Constants.hpp"

Light& Light::operator=(const Light& rhs) {
    if (this == &rhs) {
        return (*this);
    }
    return (*this);
}

// returns the radiance
RGBColor Light::L(ShadeRec& srec [[maybe_unused]]) {
    return (black);
}
