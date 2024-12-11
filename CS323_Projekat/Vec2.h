#pragma once
#include <math.h>

template<typename T>
class Vec2
{
public:
	Vec2() = default;
	Vec2(T x, T y)
		:
		x(x),
		y(y)
	{
	}
	Vec2 operator+(const Vec2& rhs) const
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}
	Vec2 operator-(const Vec2& rhs) const
	{
		return Vec2(x - rhs.x, y - rhs.y);
	}
	Vec2 operator*(const Vec2& rhs) const
	{
		return Vec2(x * rhs.x, y * rhs.y);
	}
	Vec2 operator/(const Vec2& rhs) const
	{
		return Vec2(x / rhs.x, y / rhs.y);
	}
	Vec2& operator*=(const Vec2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Vec2& operator+=(const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Vec2& operator=(const Vec2& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	float GetLength() const
	{
		return sqrt(x * x + y * y);
	}
	Vec2 GetNormalized() const
	{
		float length = GetLength();
		if (length == 0)
		{
			return Vec2(0, 0);
		}
		return Vec2(x / length, y / length);
	}
public:
	T x;
	T y;
};

typedef Vec2<int> Vei2;
typedef Vec2<float> Vef2;
