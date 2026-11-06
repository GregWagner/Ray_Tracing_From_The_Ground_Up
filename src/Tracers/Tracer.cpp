#include "Tracer.hpp"

Tracer::Tracer() : world_ptr(nullptr) {}

Tracer::Tracer(World* _worldPtr) : world_ptr(_worldPtr) {}

Tracer::~Tracer() {
    if (world_ptr != nullptr) {
        world_ptr = nullptr;
    }
}

RGBColor Tracer::trace_ray(const Ray& ray [[maybe_unused]]) const {
    return (black);
}

RGBColor Tracer::trace_ray(const Ray ray [[maybe_unused]],
                           const int depth [[maybe_unused]]) const {
    return (black);
}
