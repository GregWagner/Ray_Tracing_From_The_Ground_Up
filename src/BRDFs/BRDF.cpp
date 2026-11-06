#include "BRDF.hpp"
#include "Constants.hpp"

BRDF::BRDF() {}

BRDF::BRDF(const BRDF& brdf [[maybe_unused]]) {}

BRDF& BRDF::operator=(const BRDF& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	return (*this);
}

BRDF::~BRDF() {}

RGBColor BRDF::f(const ShadeRec& srec [[maybe_unused]],
				 const Vector3D& wo [[maybe_unused]],
				 const Vector3D& wi [[maybe_unused]]) const {
	return (black);
}

RGBColor BRDF::sample_f(const ShadeRec& srec [[maybe_unused]],
						const Vector3D& wo [[maybe_unused]],
						Vector3D& wi [[maybe_unused]]) const {
	return (black);
}

RGBColor BRDF::sample_f(const ShadeRec& srec [[maybe_unused]],
						const Vector3D& wo [[maybe_unused]],
						Vector3D& wi [[maybe_unused]],
						float& pdf [[maybe_unused]]) const {
	return (black);
}

RGBColor BRDF::rho(const ShadeRec& srec [[maybe_unused]],
				   const Vector3D& wo [[maybe_unused]]) const {
	return (black);
}
