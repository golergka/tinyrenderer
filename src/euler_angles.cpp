#include "euler_angles.h"

Matrix<4,4> EulerAngles::get_rotation()
{
	return rotate_by_x(x) * rotate_by_y(y) * rotate_by_z(z);
}
