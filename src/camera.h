#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "euler_angles.h"
#include "vec3.h"

class Camera
{
public:
	Camera();
	Camera(EulerAngles _angles, Vec3f _position);

	Matrix<4,4> local_to_world() const;
	Matrix<4,4> world_to_local() const;
}

#endif // __CAMERA_H__
