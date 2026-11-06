#include "Tracer.hpp"

// -------------------------------------------------------------------- default constructor

Tracer::Tracer()
	: world_ptr(nullptr) {}


// -------------------------------------------------------------------- constructor

Tracer::Tracer(World* _worldPtr)
	: world_ptr(_worldPtr) {}


// -------------------------------------------------------------------- destructor

Tracer::~Tracer() {
	if (world_ptr)
		world_ptr = nullptr;
}


// -------------------------------------------------------------------- trace_ray

RGBColor
Tracer::trace_ray(const Ray& ray [[maybe_unused]]) const {
	return (black);
}


// -------------------------------------------------------------------- trace_ray

RGBColor
Tracer::trace_ray(const Ray ray [[maybe_unused]], const int depth [[maybe_unused]]) const {
	return (black);
}
