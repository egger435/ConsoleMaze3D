#pragma once
class vec2
{
private:
	double x;  //��ά����x����
	double y;  //��ά����y����
public:
	double GetX();
	double GetY();
	vec2(double x = 0, double y = 0);
	vec2 operator + (const vec2& v);
	vec2 operator - (const vec2& v);
	double operator * (const vec2& v);
	vec2 operator * (double k);
	vec2 operator / (double k);
	vec2 operator += (const vec2& v);
	vec2 operator -= (const vec2& v);
	vec2 operator *= (double k);
	vec2 operator /= (double k);
	vec2 operator - ();
	double magnitute2();
	double magnitute();
	vec2 normalize();

};

