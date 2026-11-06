#pragma once

#include "BRDF.hpp"

class Lambertian : public BRDF {
    public:
    Lambertian();

    Lambertian(const Lambertian& lamb);

    [[nodiscard]] Lambertian* clone() const override;

    ~Lambertian() override;

    Lambertian& operator=(const Lambertian& rhs);

    [[nodiscard]] RGBColor f(const ShadeRec& sr, const Vector3D& wo,
                             const Vector3D& wi) const override;

    [[nodiscard]] RGBColor rho(const ShadeRec& sr,
                               const Vector3D& wo) const override;

    void set_ka(const float ka);

    void set_kd(const float kd);

    void set_cd(const RGBColor& c);

    void set_cd(const float r, const float g, const float b);

    void set_cd(const float c);

    private:
    float kd;
    RGBColor cd;
};

inline void Lambertian::set_ka(const float k) {
    kd = k;
}

inline void Lambertian::set_kd(const float k) {
    kd = k;
}

inline void Lambertian::set_cd(const RGBColor& c) {
    cd = c;
}

inline void Lambertian::set_cd(const float r, const float g, const float b) {
    cd.r = r;
    cd.g = g;
    cd.b = b;
}

inline void Lambertian::set_cd(const float c) {
    cd.r = c;
    cd.g = c;
    cd.b = c;
}