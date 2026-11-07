#ifndef TRACER_HPP
#define TRACER_HPP

// The tracer classes have no copy constructor, assignment operator. or clone
// function because of the world pointer, which should not be assigned or copy
// constructed See comments in the World.h file.


#include "Constants.hpp"
#include "RGBColor.hpp"
#include "Ray.hpp"

class World;

class Tracer {
    public:
    Tracer();

    explicit Tracer(World* _world_ptr);

    Tracer(Tracer&& tracer) = default;

    virtual ~Tracer();

    Tracer& operator=(Tracer&& tracer) = default;

    [[nodiscard]] virtual RGBColor trace_ray(const Ray& ray) const;

    [[nodiscard]] virtual RGBColor trace_ray(const Ray& ray,
                                             const int depth) const;

    protected:
    World* world_ptr;
};

#endif
