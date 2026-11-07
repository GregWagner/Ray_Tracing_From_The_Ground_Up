#pragma once

#include "Tracer.hpp"

class MultipleObjects : public Tracer {
    public:
    MultipleObjects();

    explicit MultipleObjects(World* _world_ptr);

    MultipleObjects(MultipleObjects&& other) = default;

    ~MultipleObjects() override;

    MultipleObjects& operator=(MultipleObjects&& other) = default;

    [[nodiscard]] RGBColor trace_ray(const Ray& ray) const override;

    using Tracer::trace_ray;
};