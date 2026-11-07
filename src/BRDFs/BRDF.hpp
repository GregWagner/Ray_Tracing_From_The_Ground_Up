#ifndef BRDF_HPP
#define BRDF_HPP

#include "RGBColor.hpp"
#include "ShadeRec.hpp"
#include "Vector3D.hpp"

class BRDF {
    public:
    BRDF() = default;

    BRDF(const BRDF& brdf [[maybe_unused]]) = default;

    BRDF(BRDF&& brdf [[maybe_unused]]) = default;

    [[nodiscard]]
    virtual BRDF* clone() const = 0;

    virtual ~BRDF();

    virtual RGBColor f(const ShadeRec& srec, const Vector3D& wo,
                       const Vector3D& wi) const;

    virtual RGBColor sample_f(const ShadeRec& srec, const Vector3D& wo,
                              Vector3D& wi) const;

    virtual RGBColor sample_f(const ShadeRec& srec, const Vector3D& wo,
                              Vector3D& wi, float& pdf) const;

    virtual RGBColor rho(const ShadeRec& srec, const Vector3D& wo) const;

    protected:
    BRDF& operator=(const BRDF& rhs);
};

#endif
