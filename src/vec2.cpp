#include "vec2.h"
#include <cmath>

double vec2::GetX()
{
	return x;
}

double vec2::GetY()
{
	return y;
}

vec2::vec2(double x, double y)
{
	this->x = x;
	this->y = y;
}

vec2 vec2::operator+(const vec2& v)
{
	return vec2(x + v.x, y + v.y);
}

vec2 vec2::operator-(const vec2& v)
{
	return vec2(x - v.x, y - v.y);
}

double vec2::operator*(const vec2& v)
{
	return x * v.x + y * v.y;
}

vec2 vec2::operator*(double k)
{
	return vec2(k * x, k * y);
}

vec2 vec2::operator/(double k)
{
	return vec2(x / k, y / k);
}

vec2 vec2::operator+=(const vec2& v)
{
	x += v.x;
	y += v.y;
	return vec2(x, y);
}

vec2 vec2::operator-=(const vec2& v)
{
	x -= v.x;
	y -= v.y;
	return vec2(x, y);
}

vec2 vec2::operator*=(double k)
{
	x *= k;
	y *= k;
	return vec2(x, y);
}

vec2 vec2::operator/=(double k)
{
	x /= k;
	y /= k;
	return vec2(x, y);
}

vec2 vec2::operator-()
{
	return vec2(-x, -y);
}

double vec2::magnitute2()
{
	return x * x + y * y;
}

double vec2::magnitute()
{
	return sqrt(magnitute2());
}

vec2 vec2::normalize()
{
	double mag = magnitute();
	(*this) /= mag;
	return *this;
}
