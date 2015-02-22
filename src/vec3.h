#ifndef __VEC3_H__
#define __VEC3_H__

#include <cmath>
#include <ostream>

template <class t> struct Vec3
{
	union
	{
		struct {t x, y, z; };
		struct {t ivert, iuv, inorm; };
		t raw[3];
	};

	Vec3() : x(0), y(0), z(0) {}
	Vec3(t _x, t _y, t _z) : x(_x), y(_y), z(_z) {}

	inline Vec3<t> operator ^(const Vec3<t> &v) const
	{
		return Vec3<t> (
				y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x
			);
	}

	inline Vec3<t> operator +(const Vec3<t> &v) const
	{
		return Vec3<t> (x + v.x, y + v.y, z + v.z);
	}

	inline Vec3<t> operator -(const Vec3<t> &v) const
	{
		return Vec3<t> (x - v.x, y - v.y, z - v.z);
	}

	inline Vec3<t> operator *(float f) const
	{
		return Vec3<t> (x * f, y * f, z * f);
	}

	inline t operator *(const Vec3<t> &v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}
	
	float norm() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	Vec3<t> & normalize(t l=1)
	{
		*this = (*this)*(l/norm());
		return *this;
	}

	t& operator[] (const int i)
	{
		return i <= 0 ?
				x : (
					i == 1 ?
					y : z);
	}

	template <class> friend std::ostream& operator<<(std::ostream& s, Vec2<t>& v);
};

typedef Vec3<float> Vec3f;
typedef Vec3<int>	Vec3i;

template <class t> std::ostream& operator <<(std::ostream& s, Vec3<t>& v)
{
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
	return s;
}

#endif // __VEC3_H__
