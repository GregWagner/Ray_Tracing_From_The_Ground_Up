#include "World.hpp"
#include "Constants.hpp"

// geometric objects
#include "Plane.hpp"
#include "Sphere.hpp"

// tracers
#include "MultipleObjects.hpp"
#include "RayCast.hpp"
#include "SingleSphere.hpp"

// cameras
#include "Pinhole.hpp"

// lights
#include "Directional.hpp"

// materials
#include "Matte.hpp"

// utilities
#include "Maths.hpp"
#include "Normal.hpp"
#include "Point3D.hpp"
#include "ShadeRec.hpp"
#include "Vector3D.hpp"

// tracer_ptr is set to NULL because the build functions will always construct
// the appropriate tracer ambient_ptr is set to a default ambient light because
// this will do for most scenes camera_ptr is set to NULL because the build
// functions will always have to construct a camera and set its parameters

World::World()
    : background_color(black), tracer_ptr(nullptr), ambient_ptr(new Ambient),
      camera_ptr(nullptr) {}

World::~World() {
    if (tracer_ptr != nullptr) {
        delete tracer_ptr;
        tracer_ptr = nullptr;
    }

    if (ambient_ptr != nullptr) {
        delete ambient_ptr;
        ambient_ptr = nullptr;
    }

    if (camera_ptr != nullptr) {
        delete camera_ptr;
        camera_ptr = nullptr;
    }

    delete_objects();
    delete_lights();
}

// This uses orthographic viewing along the zw axis
void World::build() {
    vp.set_hres(800);
    vp.set_vres(800);
    vp.set_pixel_size(1.0f);
    vp.set_samples(1);
    vp.set_gamma(1.0f);

    tracer_ptr = new RayCast(this);

    auto* pinhole = new Pinhole();
    pinhole->set_eye(0, 0, 500);
    pinhole->set_lookat(0, 0, 0);
    pinhole->set_up_vector(0, 1, 0);
    pinhole->compute_uvw();
    pinhole->set_view_distance(500);
    pinhole->set_zoom(1.0);
    camera_ptr = pinhole;

    auto* renderSphere = new Sphere(Point3D(0, 0, 0), 80);
    auto* matte = new Matte();
    matte->set_ka(0.25f);
    matte->set_kd(0.6f);
    matte->set_cd(1.0f);
    renderSphere->set_material(matte);
    add_object(renderSphere);

    auto* directional = new Directional();
    directional->scale_radiance(3.0f);
    directional->set_color(1.0f);
    directional->set_direction(1, 1, 1);
    add_light(directional);
}

// This uses orthographic viewing along the zw axis
void World::render_scene() const {
    RGBColor pixel_color;
    Ray ray;
    int const hres = vp.hres;
    int const vres = vp.vres;
    float const s = vp.s;
    float const zw = 100.0; // hardwired in

    ray.d = Vector3D(0, 0, -1);

    for (int r = 0; r < vres; r++) {      // up
        for (int c = 0; c <= hres; c++) { // across
            ray.o =
                Point3D(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw);
            pixel_color = tracer_ptr->trace_ray(ray);
            display_pixel(r, c, pixel_color);
        }
    }
}

// clamp
RGBColor World::max_to_one(const RGBColor& c) const {
    float const max_value = max(c.r, max(c.g, c.b));

    if (max_value > 1.0) {
        return (c / max_value);
    } else {
        return (c);
    }
}

// Set color to red if any component is greater than one
RGBColor World::clamp_to_color(const RGBColor& raw_color) const {
    RGBColor c(raw_color);

    if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
        c.r = 1.0;
        c.g = 0.0;
        c.b = 0.0;
    }

    return (c);
}

ShadeRec World::hit_objects(const Ray& ray) {
    ShadeRec sr(*this);
    double t;
    Normal normal;
    Point3D local_hit_point;
    float tmin = kHugeValue;
    for (GeometricObject* object : objects) {
        if (object->hit(ray, t, sr) && (t < tmin)) {
            sr.hit_an_object = true;
            tmin = t;
            sr.material_ptr = object->get_material();
            sr.hit_point = ray.o + t * ray.d;
            normal = sr.normal;
            local_hit_point = sr.local_hit_point;
        }
    }

    if (sr.hit_an_object) {
        sr.t = tmin;
        sr.normal = normal;
        sr.local_hit_point = local_hit_point;
    }

    return (sr);
}

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's
// empty
void World::delete_objects() {
    for (GeometricObject* object : objects) {
        delete object;
    }

    objects.clear();
}

void World::delete_lights() {
    for (Light* light : lights) {
        delete light;
    }

    lights.clear();
}
