// this file contains the definition of the class GeometricObject

#include "Constants.hpp"
#include "Material.hpp"
#include "GeometricObject.hpp"


// ---------------------------------------------------------------------- default constructor


GeometricObject::GeometricObject()
	: material_ptr(nullptr) {}


// ---------------------------------------------------------------------- copy constructor

GeometricObject::GeometricObject(const GeometricObject& object) {
	if (object.material_ptr)
		material_ptr = object.material_ptr->clone();
	else
		material_ptr = nullptr;
}


// ---------------------------------------------------------------------- assignment operator

GeometricObject&
GeometricObject::operator=(const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);

	if (material_ptr) {
		delete material_ptr;
		material_ptr = nullptr;
	}

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();

	return (*this);
}


// ---------------------------------------------------------------------- destructor

GeometricObject::~GeometricObject() {
	if (material_ptr) {
		delete material_ptr;
		material_ptr = nullptr;
	}
}


// ---------------------------------------------------------------- set_material

void GeometricObject::set_material(Material* mPtr) {
	material_ptr = mPtr;
}
