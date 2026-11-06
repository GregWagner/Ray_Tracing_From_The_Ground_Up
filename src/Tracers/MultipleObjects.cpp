#include "MultipleObjects.hpp"
#include "World.hpp"

// -------------------------------------------------------------------- default constructor

MultipleObjects::MultipleObjects()
	: Tracer() {}


// -------------------------------------------------------------------- constructor

MultipleObjects::MultipleObjects(World* _worldPtr)
	: Tracer(_worldPtr) {}


// -------------------------------------------------------------------- destructor

MultipleObjects::~MultipleObjects() {}


// -------------------------------------------------------------------- trace_ray

RGBColor
MultipleObjects::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed

	if (sr.hit_an_object)
		return (sr.color);
	else
		return (world_ptr->background_color);
}
