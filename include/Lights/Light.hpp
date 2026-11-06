#ifndef __LIGHT__
#define __LIGHT__

#include "Vector3D.hpp"
#include "RGBColor.hpp"
#include "Ray.hpp"

class ShadeRec;


//-------------------------------------------------------------------- class Light

class Light {
	public:
	Light();

	Light(const Light& ls);

	Light&
	operator=(const Light& rhs);

	[[nodiscard]] virtual Light*
	clone() const = 0;

	virtual ~Light();

	[[nodiscard]] virtual Vector3D
	get_direction(ShadeRec& sr) = 0;

	[[nodiscard]] virtual RGBColor
	L(ShadeRec& sr);
};

#endif