#include "GeometricObject.hpp"
#include "Material.hpp"

#include <utility>

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

GeometricObject::GeometricObject(GeometricObject&& object) noexcept
    : material_ptr(object.material_ptr) {
    object.material_ptr = nullptr;
}

GeometricObject& GeometricObject::operator=(GeometricObject&& rhs) noexcept {
    if (this != &rhs) {
        delete material_ptr;
        material_ptr = rhs.material_ptr;
        rhs.material_ptr = nullptr;
    }

    return (*this);
}

void GeometricObject::set_material(Material* mPtr) {
    if (mPtr != material_ptr) {
        delete material_ptr;
    }

    material_ptr = mPtr;
}
