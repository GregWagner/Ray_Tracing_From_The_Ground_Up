#ifndef __PLANE__
#define __PLANE__

#include "GeometricObject.hpp"

//-------------------------------------------------------------------- class Plane

class Plane : public GeometricObject {
	public:
	Plane(); // default constructor

	Plane(const Point3D& point, const Normal& normal); // constructor

	Plane(const Plane& plane); // copy constructor

	[[nodiscard]] virtual Plane* // virtual copy constructor
	clone() const override;

	Plane& // assignment operator
	operator=(const Plane& rhs);

	virtual // destructor
		~Plane() override;

	[[nodiscard]] virtual bool
	hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;

	private:
	Point3D a; // point through which plane passes
	Normal n;  // normal to the plane

	static const double kEpsilon; // for shadows and secondary rays
};

#endif
