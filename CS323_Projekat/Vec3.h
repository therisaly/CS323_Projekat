#pragma once
#include <math.h>

template<typename T>
class Vec3
{
public:
	Vec3() = default;
	Vec3(T x, T y, T z)
		:
		x(x),
		y(y),
		z(z)
	{
	}
	Vec3 operator+(const Vec3& rhs) const
	{
		return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	Vec3 operator-(const Vec3& rhs) const
	{
		return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	Vec3 operator*(const Vec3& rhs) const
	{
		return Vec3(x * rhs.x, y * rhs.y, z * rhs.z);
	}
	Vec3 operator/(const Vec3& rhs) const
	{
		return Vec3(x / rhs.x, y / rhs.y, z / rhs.z); 
	}
	Vec3& operator*=(const Vec3& rhs) 
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}
	Vec3& operator-=(const Vec3& rhs) 
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	Vec3& operator+=(const Vec3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	Vec3& operator+=(const float rhs)
	{
		x += rhs;
		y += rhs;
		z += rhs;
		return *this;
	}
	Vec3& operator=(const Vec3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;

		return *this;
	}
	float GetLength() const
	{
		return sqrt(x * x + y * y + z * z);
	}
	Vec3 GetNormalized() const
	{
		float length = GetLength();
		if (length == 0) 
		{
			return Vec3(0, 0, 0); 
		}
		return Vec3(x / length, y / length, z / length);
	}
 public:
	T x;
	T y;
	T z;
};

typedef Vec3<int> Vei3;
typedef Vec3<float> Vef3;
