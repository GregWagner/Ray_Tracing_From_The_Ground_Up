
#include "ViewPlane.hpp"

ViewPlane::ViewPlane()
    : hres(400), vres(400), s(1.0), num_samples(1), gamma(1.0), inv_gamma(1.0),
      show_out_of_gamut(false) {}

ViewPlane::ViewPlane(const ViewPlane& vp) = default;

ViewPlane& ViewPlane::operator=(const ViewPlane& rhs) {
    if (this == &rhs) {
        return (*this);
    }

    hres = rhs.hres;
    vres = rhs.vres;
    s = rhs.s;
    num_samples = rhs.num_samples;
    gamma = rhs.gamma;
    inv_gamma = rhs.inv_gamma;
    show_out_of_gamut = rhs.show_out_of_gamut;

    return (*this);
}
