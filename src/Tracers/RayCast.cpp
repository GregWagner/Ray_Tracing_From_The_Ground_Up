#include "RayCast.hpp"
#include "Material.hpp"
#include "ShadeRec.hpp"
#include "World.hpp"

RayCast::RayCast() : Tracer() {}

RayCast::RayCast(World* _worldPtr) : Tracer(_worldPtr) {}

RayCast::~RayCast() = default;

RGBColor RayCast::trace_ray(const Ray& ray) const {
    ShadeRec sr(world_ptr->hit_objects(ray));

    if (sr.hit_an_object) {
        sr.ray = ray; // used for specular shading
        return (sr.material_ptr->shade(sr));
    }
    return (world_ptr->background_color);
}

// this ignores the depth argument

RGBColor RayCast::trace_ray(const Ray& ray,
                            const int depth [[maybe_unused]]) const {
    ShadeRec sr(world_ptr->hit_objects(ray));

    if (sr.hit_an_object) {
        sr.ray = ray; // used for specular shading
        return (sr.material_ptr->shade(sr));
    }
    return (world_ptr->background_color);
}
