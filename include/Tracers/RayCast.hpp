#ifndef __RAY_CAST__
#define __RAY_CAST__

#include "Tracer.hpp"

class RayCast : public Tracer {
    public:
    RayCast();

    explicit RayCast(World* _worldPtr);

    virtual ~RayCast() override;

    [[nodiscard]] virtual RGBColor trace_ray(const Ray& ray) const override;

    [[nodiscard]] virtual RGBColor trace_ray(const Ray ray,
                                             const int depth) const override;
};

#endif
