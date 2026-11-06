#ifndef __AMBIENT__
#define __AMBIENT__

#include "Light.hpp"

class Ambient : public Light {
public:
  Ambient();

  Ambient(const Ambient &a);

  [[nodiscard]] virtual Light *clone() const override;

  Ambient &operator=(const Ambient &rhs);

  virtual ~Ambient() override;

  void scale_radiance(const float b);

  void set_color(const float c);

  void set_color(const RGBColor &c);

  void set_color(const float r, const float g, const float b);

  [[nodiscard]] virtual Vector3D get_direction(ShadeRec &s) override;

  [[nodiscard]] virtual RGBColor L(ShadeRec &s) override;

private:
  float ls;
  RGBColor color;
};

inline void Ambient::scale_radiance(const float b) { ls = b; }

inline void Ambient::set_color(const float c) {
  color.r = c;
  color.g = c;
  color.b = c;
}

inline void Ambient::set_color(const RGBColor &c) { color = c; }

inline void Ambient::set_color(const float r, const float g, const float b) {
  color.r = r;
  color.g = g;
  color.b = b;
}

#endif
