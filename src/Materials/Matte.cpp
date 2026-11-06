#include "Matte.hpp"

Matte::Matte()
    : Material(), ambient_brdf(new Lambertian), diffuse_brdf(new Lambertian) {}

Matte::Matte(const Matte& m) : Material(m) {
    if (m.ambient_brdf != nullptr) {
        ambient_brdf = m.ambient_brdf->clone();
    } else {
        ambient_brdf = nullptr;
    }

    if (m.diffuse_brdf != nullptr) {
        diffuse_brdf = m.diffuse_brdf->clone();
    } else {
        diffuse_brdf = nullptr;
    }
}

Material* Matte::clone() const {
    return (new Matte(*this));
}

Matte& Matte::operator=(const Matte& rhs) {
    if (this == &rhs) {
        return (*this);
    }

    Material::operator=(rhs);

    if (ambient_brdf != nullptr) {
        delete ambient_brdf;
        ambient_brdf = nullptr;
    }

    if (rhs.ambient_brdf != nullptr) {
        ambient_brdf = rhs.ambient_brdf->clone();
    }

    if (diffuse_brdf != nullptr) {
        delete diffuse_brdf;
        diffuse_brdf = nullptr;
    }

    if (rhs.diffuse_brdf != nullptr) {
        diffuse_brdf = rhs.diffuse_brdf->clone();
    }

    return (*this);
}

Matte::~Matte() {
    if (ambient_brdf != nullptr) {
        delete ambient_brdf;
        ambient_brdf = nullptr;
    }

    if (diffuse_brdf != nullptr) {
        delete diffuse_brdf;
        diffuse_brdf = nullptr;
    }
}

RGBColor Matte::shade(ShadeRec& sr) {
    Vector3D const wo = -sr.ray.d;
    RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
    for (Light* light : sr.w.lights) {
        Vector3D const wi = light->get_direction(sr);
        float const ndotwi = static_cast<float>(sr.normal * wi);

        if (ndotwi > 0.0) {
            L += diffuse_brdf->f(sr, wo, wi) * light->L(sr) * ndotwi;
        }
    }

    return (L);
}
