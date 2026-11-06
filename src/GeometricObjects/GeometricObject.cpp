#include "GeometricObject.hpp"
#include "Material.hpp"

GeometricObject::GeometricObject() : material_ptr(nullptr) {}

GeometricObject::GeometricObject(const GeometricObject& object) {
    if (object.material_ptr != nullptr) {
        material_ptr = object.material_ptr->clone();
    } else {
        material_ptr = nullptr;
    }
}

GeometricObject& GeometricObject::operator=(const GeometricObject& rhs) {
    if (this == &rhs) {
        return (*this);
    }

    if (material_ptr != nullptr) {
        delete material_ptr;
        material_ptr = nullptr;
    }

    if (rhs.material_ptr != nullptr) {
        material_ptr = rhs.material_ptr->clone();
    }

    return (*this);
}

GeometricObject::~GeometricObject() {
    if (material_ptr != nullptr) {
        delete material_ptr;
        material_ptr = nullptr;
    }
}

void GeometricObject::set_material(Material* mPtr) {
    material_ptr = mPtr;
}
