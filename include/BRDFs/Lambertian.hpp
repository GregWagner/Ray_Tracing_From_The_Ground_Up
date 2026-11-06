#ifndef __LAMBERTIAN__
#define __LAMBERTIAN__

#include "BRDF.hpp"

class Lambertian : public BRDF {
	public:
	Lambertian();

	Lambertian(const Lambertian& lamb);

	[[nodiscard]] virtual Lambertian*
	clone() const override;

	~Lambertian() override;

	Lambertian&
	operator=(const Lambertian& rhs);

	[[nodiscard]] virtual RGBColor
	f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;

	[[nodiscard]] virtual RGBColor
	rho(const ShadeRec& sr, const Vector3D& wo) const override;

	void
	set_ka(const float ka);

	void
	set_kd(const float kd);

	void
	set_cd(const RGBColor& c);

	void
	set_cd(const float r, const float g, const float b);

	void
	set_cd(const float c);

	private:
	float kd;
	RGBColor cd;
};


// -------------------------------------------------------------- set_ka

inline void
Lambertian::set_ka(const float k) {
	kd = k;
}


// -------------------------------------------------------------- set_kd

inline void
Lambertian::set_kd(const float k) {
	kd = k;
}


// -------------------------------------------------------------- set_cd

inline void
Lambertian::set_cd(const RGBColor& c) {
	cd = c;
}


// ---------------------------------------------------------------- set_cd

inline void
Lambertian::set_cd(const float r, const float g, const float b) {
	cd.r = r;
	cd.g = g;
	cd.b = b;
}


// ---------------------------------------------------------------- set_cd

inline void
Lambertian::set_cd(const float c) {
	cd.r = c;
	cd.g = c;
	cd.b = c;
}

#endif
