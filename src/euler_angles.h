#ifndef __EULER_ANGLES_H__
#define __EULER_ANGLES_H__

#include "matrix.h"

// z-x-y rotation order
struct EulerAngles : Vec3f
{
public:
	EulerAngles() : Vec3f() {}
	EulerAngles(float _x, float _y, float _z) : Vec3f(_x, _y, _z) {}

	Matrix<4,4> get_rotation();
};

#endif // __EULER_ANGLES_H__
