#pragma once

class Material;

#include "Point3D.hpp"
#include "Ray.hpp"
#include "ShadeRec.hpp"

class GeometricObject {
    public:
    GeometricObject();

    GeometricObject(const GeometricObject& object);

    GeometricObject(GeometricObject&& object) noexcept;

    [[nodiscard]] virtual GeometricObject* clone() const = 0;

    virtual ~GeometricObject();

    [[nodiscard]] virtual bool hit(const Ray& ray, double& t,
                                   ShadeRec& s) const = 0;

    [[nodiscard]] Material* get_material() const;

    virtual void // needs to virtual so that it can be overriden in Compound
    set_material(Material* mPtr);

    protected:
    mutable Material*
        material_ptr; // mutable allows Compound::hit, Instance::hit and Grid::hit
                      // to assign to material_ptr. hit functions are const

    GeometricObject& operator=(const GeometricObject& rhs);

    GeometricObject& operator=(GeometricObject&& rhs) noexcept;
};

inline Material* GeometricObject::get_material() const {
    return (material_ptr);
}