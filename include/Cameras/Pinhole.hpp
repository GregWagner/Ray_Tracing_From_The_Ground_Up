#ifndef __PINHOLE__
#define __PINHOLE__

// This file contains the declaration of the class Pinhole

#include "Point2D.hpp"
#include "World.hpp" // we can #include "World.hpp" here

// class Pinhole

class Pinhole : public Camera {
    public:
    Pinhole();

    Pinhole(const Pinhole& ph);

    [[nodiscard]] Camera* clone() const override;

    Pinhole& operator=(const Pinhole& rhs);

    ~Pinhole() override;

    void set_view_distance(const float vpd);

    void set_zoom(const float zoom_factor);

    [[nodiscard]] Vector3D get_direction(const Point2D& p) const;

    void render_scene(const World& w) override;

    private:
    float d;    // view plane distance
    float zoom; // zoom factor
};

// set_vpd
inline void Pinhole::set_view_distance(float _d) {
    d = _d;
}

inline void Pinhole::set_zoom(float zoom_factor) {
    zoom = zoom_factor;
}

#endif
