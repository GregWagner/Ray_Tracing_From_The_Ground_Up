#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__

#include "Tracer.hpp"

class MultipleObjects : public Tracer {
	public:
	MultipleObjects(void);

	MultipleObjects(World* _world_ptr);

	virtual ~MultipleObjects(void);

	virtual RGBColor
	trace_ray(const Ray& ray) const;

	using Tracer::trace_ray;
};

#endif
