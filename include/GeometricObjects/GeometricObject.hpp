#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

class Material;

#include "Point3D.hpp"
#include "Ray.hpp"
#include "ShadeRec.hpp"


//----------------------------------------------------------------------------------------------------- Class GeometricObject

class GeometricObject {
	public:
	GeometricObject(); // default constructor

	GeometricObject(const GeometricObject& object); // copy constructor

	virtual GeometricObject* // virtual copy constructor
	clone() const = 0;

	virtual // destructor
		~GeometricObject();

	virtual bool
	hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

	Material*
	get_material() const;

	virtual void // needs to virtual so that it can be overriden in Compound
	set_material(Material* mPtr);


	protected:
	mutable Material* material_ptr; // mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const

	GeometricObject& // assignment operator
	operator=(const GeometricObject& rhs);
};


// ------------------------------------------------------------------------- get_material

inline Material*
GeometricObject::get_material() const {
	return (material_ptr);
}

#endif