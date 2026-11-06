#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__

#include "Tracer.hpp"

class MultipleObjects : public Tracer {
	public:
	MultipleObjects();

	explicit MultipleObjects(World* _world_ptr);

	virtual ~MultipleObjects() override;

	[[nodiscard]] virtual RGBColor
	trace_ray(const Ray& ray) const override;

	using Tracer::trace_ray;
};

#endif
