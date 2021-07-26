#pragma once
#include "Settings.h"

#define PI 3.141592741f
#define PI_DOUBLE 6.283185482f
#define PI_HALF 1.570796371f
#define PI_SQUARE 9.869604111f
#define E 2.718281746f
#define RAD_PER_DEG 0.01745329238f
#define DEG_PER_RAD 57.29578018f

Radian ToRadian(Degree degree);
Degree ToDegree(Radian radian);

//각도를 -180~180 범위로 정규화한다.
Degree NormalizeDegree(Degree degree);
Radian NormalizeRadian(Radian radian);

float Sin(Degree angle);
float Cos(Degree angle);
float Tan(Degree angle);

Degree Arctan2(float y, float x);

template<typename T>
T Clamp(T value, T min, T max);
template<typename T>
T Wrap(T value, T min, T max);
template<typename T>
void Swap(T& a, T& b);
template<typename T>
T Abs(T a);
template<typename T>
const T& Max(const T& a, const T& b);
template<typename T>
const T& Min(const T& a, const T& b);
template<typename T>
T Sign(T value);

class Size2F :public D2D1_SIZE_F
{
public:
	Size2F(void);
	Size2F(float cx, float cy);

	Size2F operator +(const Size2F &s) const;
	Size2F operator -(const Size2F &s) const;
	Size2F operator /(const Size2F &s) const;
	Size2F operator *(const Size2F &s) const;

	Size2F operator -(void) const;

	Size2F& operator +=(const Size2F &s);
	Size2F& operator -=(const Size2F &s);
	Size2F& operator /=(const Size2F &s);
	Size2F& operator *=(const Size2F &s);

	bool operator ==(const Size2F &s) const;
	bool operator !=(const Size2F &s) const;

	void Set(const Size2F &s);
	void Set(float cx, float cy);
};

class Size2U :public D2D1_SIZE_U
{
public:
	Size2U();
	Size2U(unsigned int cx, unsigned int cy);

	Size2U operator +(const Size2U &s) const;
	Size2U operator -(const Size2U &s) const;
	Size2U operator /(const Size2U &s) const;
	Size2U operator *(const Size2U &s) const;
	Size2U& operator +=(const Size2U &s);
	Size2U& operator -=(const Size2U &s);
	Size2U& operator /=(const Size2U &s);
	Size2U& operator *=(const Size2U &s);

	bool operator ==(const Size2U &s) const;
	bool operator !=(const Size2U &s) const;

	void Set(const Size2U &s);
	void Set(unsigned int cx, unsigned int cy);
};

class Vec2F : public D2D1_POINT_2F
{
public:
	Vec2F();
	Vec2F(float x, float y);

	operator float*(void);
	operator const float*(void) const;

	Vec2F operator +(const Vec2F &v) const;
	Vec2F operator -(const Vec2F &v) const;
	Vec2F operator /(const Vec2F &v) const;
	Vec2F operator *(const Vec2F &v) const;

	Vec2F operator *(float f) const;
	Vec2F operator /(float f) const;

	Vec2F operator -(void) const;

	Vec2F& operator +=(const Vec2F &v);
	Vec2F& operator -=(const Vec2F &v);
	Vec2F& operator /=(const Vec2F &v);
	Vec2F& operator *=(const Vec2F &v);

	Vec2F& operator *=(float f);
	Vec2F& operator /=(float f);

	bool operator ==(const Vec2F &v) const;
	bool operator !=(const Vec2F &v) const;

	float Dot(const Vec2F &b);
	float Cross(const Vec2F &a, const Vec2F &b);
	Vec2F Cross(const Vec2F &a, float s);
	Vec2F Cross(float s, const Vec2F &a);

	
	Vec2F Normalize();

	Degree Angle() const;
	Degree Angle(const Vec2F& v)const;

	float Size();
	float Distance(const Vec2F& v)const;
	float DistanceSquare(const Vec2F& v)const;

	void Transform(float x, float y);
	void Transform(const Vec2F &v);

	void Set(const Vec2F &v);
	void Set(float x, float y);
};
Vec2F operator *(float f, const Vec2F &v);
float Distance(const Vec2F& a, const Vec2F& b);
float DistanceSquare(const Vec2F& a, const Vec2F& b);
Degree Angle(const Vec2F& a, const Vec2F& b);

using Point2F = Vec2F;

class Vec2L : public D2D1_POINT_2L
{
public:
	Vec2L();
	Vec2L(long x, long y);
	operator long*(void);
	operator const long*(void) const;
	
	Vec2L operator +(const Vec2L &v) const;
	Vec2L operator -(const Vec2L &v) const;
	Vec2L operator /(const Vec2L &v) const;
	Vec2L operator *(const Vec2L &v) const;

	Vec2L operator *(long l) const;
	Vec2L operator /(long l) const;

	Vec2L operator -(void) const;

	Vec2L& operator +=(const Vec2L &v);
	Vec2L& operator -=(const Vec2L &v);
	Vec2L& operator /=(const Vec2L &v);
	Vec2L& operator *=(const Vec2L &v);

	Vec2L& operator *=(long l);
	Vec2L& operator /=(long l);

	bool operator ==(const Vec2L &v) const;
	bool operator !=(const Vec2L &v) const;

	float Dot(const Vec2L &b);
	float Cross(const Vec2L &a, const Vec2L &b);
	Vec2L Cross(const Vec2L &a, long s);
	Vec2L Cross(long s, const Vec2L &a);

	Vec2L Normalize();
	Degree Angle() const;
	Degree Angle(const Vec2L& v) const;

	float Size();
	float Distance(const Vec2L & v) const;
	float DistanceSquare(const Vec2L & v) const;

	void Transform(long x, long y);
	void Transform(const Vec2L &v);

	void Set(const Vec2L &v);
	void Set(long x, long y);
};
Vec2L operator *(long l, const Vec2L &v);
float Distance(const Vec2L& a, const Vec2L& b);
float DistanceSquare(const Vec2L& a, const Vec2L& b);
Degree Angle(const Vec2L& a, const Vec2L& b);

using Point2L = Vec2L;

using ColorType = D2D1::ColorF::Enum;
using ARGB = unsigned long;
class Color : public D2D1_COLOR_F
{
public:
	Color();
	Color(ColorType color);
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);
	Color(ARGB color);

	operator ARGB(void) const;

	Color operator +(const Color &c) const;
	Color operator -(const Color &c) const;
	Color operator /(const Color &c) const;
	Color operator *(const Color &c) const;

	Color operator +(float f) const;
	Color operator -(float f) const;
	Color operator /(float f) const;
	Color operator *(float f) const;

	Color& operator +=(const Color &c);
	Color& operator -=(const Color &c);
	Color& operator /=(const Color &c);
	Color& operator *=(const Color &c);

	Color& operator +=(float f);
	Color& operator -=(float f);
	Color& operator /=(float f);
	Color& operator *=(float f);

	Color& operator =(ARGB ulcolor);

	bool operator ==(const Color &c) const;
	bool operator ==(ARGB ulcolor) const;
	bool operator !=(const Color &c) const;
	bool operator !=(ARGB ulcolor) const;

	void Set(const Color &c);
	void Set(float r, float g, float b);
	void Set(float r, float g, float b, float a);
	void Set(ARGB ulcolor);
};
//GetPos 반환 기준
//0 1 2
//3 4 5
//6 7 8
enum CritRectPos {
	LEFT_TOP,CENTER_TOP,RIGHT_TOP,
	LEFT_CENTER, CENTER, RIGHT_CENTER,
	LEFT_BOTTOM, CENTER_BOTTOM, RIGHT_BOTTOM
};

class Rect :public D2D1_RECT_F
{
public:
	Rect();
	Rect(float left, float top, float right, float bottom);
	Rect(const Vec2F& lt, const Vec2F& rb);
	bool operator ==(const Rect &other) const;
	bool operator !=(const Rect &other) const;
	float GetCenterX() const;
	float GetCenterY() const;

	Vec2F GetCenter() const;
	Vec2F GetPos(CritRectPos critPos = LEFT_TOP) const;
	float GetWidth() const;
	float GetHeight() const;
	Rect Offset(const Vec2F& offset) const;
	
	//충돌하는지만 확인함
	bool IsIntersect(const Rect& other)const;
	//bool IsIntersect(const RectL& other)const;
	bool IsIntersect(const Vec2F& other)const;
	bool IsIntersect(const Vec2L& other)const;

	//충돌하면 교집합, 충돌안하면 0, 0, 0, 0 반환
	Rect GetIntersection(const Rect& other)const;
	//Rect GetIntersection(const RecLt& other)const;
	void Set(const Rect& other);
	void Set(float left, float top, float right, float bottom);
	void Set(const Vec2F& lt, const Vec2F& rb);
};

class Circle {
public:
	float radius;
	Vec2F center;
public:
	Circle(const Vec2F& center = Vec2F(0.f, 0.f), float radius = 0.f);
	~Circle();

	Circle Offset(const Vec2F& offset) const;
};

using Matrix = D2D1_MATRIX_3X2_F;


#include"Math.inl"