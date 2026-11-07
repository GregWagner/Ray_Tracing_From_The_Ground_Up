#pragma once

#include "Tracer.hpp"

class SingleSphere : public Tracer {
    public:
    SingleSphere();

    explicit SingleSphere(World* _worldPtr);

    SingleSphere(SingleSphere&& other) = default;

    ~SingleSphere() override;

    SingleSphere& operator=(SingleSphere&& other) = default;

    [[nodiscard]] RGBColor trace_ray(const Ray& ray) const override;

    using Tracer::trace_ray;
};