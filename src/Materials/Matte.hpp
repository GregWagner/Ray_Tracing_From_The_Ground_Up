#ifndef MATTE_HPP
#define MATTE_HPP

#include "Lambertian.hpp"
#include "Material.hpp"

// class Matte

class Matte : public Material {
    public:
    Matte();

    Matte(const Matte& m);

    Matte(Matte&& m) noexcept;

    [[nodiscard]] Material* clone() const override;

    Matte& operator=(const Matte& rhs);

    Matte& operator=(Matte&& rhs) noexcept;

    ~Matte() override;

    void set_ka(const float k);

    void set_kd(const float k);

    void set_cd(const RGBColor c);

    void set_cd(const float r, const float g, const float b);

    void set_cd(const float c);

    [[nodiscard]] RGBColor shade(ShadeRec& sr) override;

    private:
    Lambertian* ambient_brdf;
    Lambertian* diffuse_brdf;
};

// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection
// is diffuse reflection

inline void Matte::set_ka(const float ka) {
    ambient_brdf->set_kd(ka);
}

// this also sets Lambertian::kd, but for a different Lambertian object

inline void Matte::set_kd(const float kd) {
    diffuse_brdf->set_kd(kd);
}

inline void Matte::set_cd(const RGBColor c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

inline void Matte::set_cd(const float r, const float g, const float b) {
    ambient_brdf->set_cd(r, g, b);
    diffuse_brdf->set_cd(r, g, b);
}

inline void Matte::set_cd(const float c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

#endif
