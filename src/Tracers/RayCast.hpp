#pragma once

#include "Tracer.hpp"

class RayCast : public Tracer {
    public:
    RayCast();

    explicit RayCast(World* _worldPtr);

    RayCast(RayCast&& other) = default;

    ~RayCast() override;

    RayCast& operator=(RayCast&& other) = default;

    [[nodiscard]] RGBColor trace_ray(const Ray& ray) const override;

    [[nodiscard]] RGBColor trace_ray(const Ray& ray,
                                     const int depth) const override;
};