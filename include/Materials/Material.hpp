#ifndef __MATERIAL__
#define __MATERIAL__

#include "World.hpp" // required for the shade function in all derived classes
#include "RGBColor.hpp"
#include "ShadeRec.hpp"

class Material {
	public:
	Material();

	Material(const Material& material);

	[[nodiscard]] virtual Material*
	clone() const = 0;

	virtual ~Material();

	[[nodiscard]] virtual RGBColor
	shade(ShadeRec& sr);

	protected:
	Material&
	operator=(const Material& rhs);
};

#endif
