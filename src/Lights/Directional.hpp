#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.hpp"
#include "RGBColor.hpp"
#include "Vector3D.hpp"

#include "ShadeRec.hpp"
#include "World.hpp" // you will need this later on for shadows

class Directional : public Light {
    public:
    Directional();

    Directional(const Directional& dl);

    [[nodiscard]] Light* clone() const override;

    Directional& operator=(const Directional& rhs);

    ~Directional() override;

    void scale_radiance(const float b);

    void set_color(const float c);

    void set_color(const RGBColor& c);

    void set_color(const float r, const float g, const float b);

    void set_direction(Vector3D d);

    void set_direction(float dx, float dy, float dz);

    [[nodiscard]] Vector3D get_direction(ShadeRec& sr) override;

    [[nodiscard]] RGBColor L(ShadeRec& sr) override;

    private:
    float ls;
    RGBColor color;
    Vector3D dir; // direction the light comes from
};

// inlined access functions
inline void Directional::scale_radiance(const float b) {
    ls = b;
}

inline void Directional::set_color(const float c) {
    color.r = c;
    color.g = c;
    color.b = c;
}

inline void Directional::set_color(const RGBColor& c) {
    color = c;
}

inline void Directional::set_color(const float r, const float g,
                                   const float b) {
    color.r = r;
    color.g = g;
    color.b = b;
}

inline void Directional::set_direction(Vector3D d) {
    dir = d;
    dir.normalize();
}

inline void Directional::set_direction(float dx, float dy, float dz) {
    dir.x = dx;
    dir.y = dy;
    dir.z = dz;
    dir.normalize();
}

#endif
