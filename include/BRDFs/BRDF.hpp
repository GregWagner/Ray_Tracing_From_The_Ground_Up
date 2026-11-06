#ifndef __BRDF__
#define __BRDF__

#include "RGBColor.hpp"
#include "ShadeRec.hpp"
#include "Vector3D.hpp"

class BRDF {
public:
  BRDF();

  BRDF(const BRDF &object);

  virtual BRDF *clone() const = 0;

  virtual ~BRDF();

  virtual RGBColor f(const ShadeRec &sr, const Vector3D &wo,
                     const Vector3D &wi) const;

  virtual RGBColor sample_f(const ShadeRec &sr, const Vector3D &wo,
                            Vector3D &wi) const;

  virtual RGBColor sample_f(const ShadeRec &sr, const Vector3D &wo,
                            Vector3D &wi, float &pdf) const;

  virtual RGBColor rho(const ShadeRec &sr, const Vector3D &wo) const;

protected:
  BRDF &operator=(const BRDF &rhs);
};

#endif
