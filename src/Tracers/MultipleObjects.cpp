#include "MultipleObjects.hpp"
#include "World.hpp"

MultipleObjects::MultipleObjects() : Tracer() {}

MultipleObjects::MultipleObjects(World* _worldPtr) : Tracer(_worldPtr) {}

MultipleObjects::~MultipleObjects() = default;

RGBColor MultipleObjects::trace_ray(const Ray& ray) const {
    ShadeRec const sr(world_ptr->hit_objects(ray)); // sr is copy constructed

    if (sr.hit_an_object) {
        return (sr.color);
    }
    return (world_ptr->background_color);
}
