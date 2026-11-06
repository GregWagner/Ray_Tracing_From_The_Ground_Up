#ifndef __SINGLE_SPHERE__
#define __SINGLE_SPHERE__

#include "Tracer.hpp"

class SingleSphere : public Tracer {
    public:
    SingleSphere();

    explicit SingleSphere(World* _worldPtr);

    ~SingleSphere() override;

    [[nodiscard]] RGBColor trace_ray(const Ray& ray) const override;

    using Tracer::trace_ray;
};

#endif
