#ifndef __CAMERA__
#define __CAMERA__

// There is no view plane distance because the fisheye and panoramic cameras
// don't use it

#include "Point3D.hpp"
#include "Vector3D.hpp"

class World; // can't #include "World" here because World contains a camera
			 // pointer

// class Camera

class Camera {
	public:
	Camera();

	Camera(const Camera& camera);

	[[nodiscard]] virtual Camera* clone() const = 0;

	virtual ~Camera();

	virtual void render_scene(const World& w) = 0;

	void set_eye(const Point3D& p);

	void set_eye(const float x, const float y, const float z);

	void set_lookat(const Point3D& p);

	void set_lookat(const float x, const float y, const float z);

	void set_up_vector(const Vector3D& u);

	void set_up_vector(const float x, const float y, const float z);

	void set_roll(const float ra);

	void set_exposure_time(const float exposure);

	void compute_uvw();

	protected:
	Point3D eye;	  // eye point
	Point3D lookat;	  // lookat point
	float ra;		  // roll angle
	Vector3D u, v, w; // orthonormal basis vectors
	Vector3D up;	  // up vector
	float exposure_time;

	Camera& operator=(const Camera& camera);
};

// inlined access functions

inline void Camera::set_eye(const Point3D& p) {
	eye = p;
}

inline void Camera::set_eye(const float x, const float y, const float z) {
	eye.x = x;
	eye.y = y;
	eye.z = z;
}

inline void Camera::set_lookat(const Point3D& p) {
	lookat = p;
}

inline void Camera::set_lookat(const float x, const float y, const float z) {
	lookat.x = x;
	lookat.y = y;
	lookat.z = z;
}

inline void Camera::set_up_vector(const Vector3D& upVector) {
	up = upVector;
}

inline void Camera::set_up_vector(const float x, const float y, const float z) {
	up.x = x;
	up.y = y;
	up.z = z;
}

inline void Camera::set_roll(const float r) {
	ra = r;
}

inline void Camera::set_exposure_time(const float exposure) {
	exposure_time = exposure;
}

#endif
