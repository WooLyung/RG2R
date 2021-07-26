#pragma once
#include"stdafx.h"
#include"Math.h"

inline Radian ToRadian(Degree degree)
{
	return degree * RAD_PER_DEG;
}

inline Degree ToDegree(Radian radian)
{
	return radian * DEG_PER_RAD;
}

inline Degree NormalizeDegree(Degree degree)
{
	return Wrap(degree, -180.f, 180.f);
}

inline Radian NormalizeRadian(Radian radian)
{
	return Wrap(radian, -PI, PI);
}

inline float Sin(Degree angle)
{
	return sinf(ToRadian(angle));
}
inline float Cos(Degree angle)
{
	return cosf(ToRadian(angle));
}
inline float Tan(Degree angle)
{
	return tanf(ToRadian(angle));
}
inline Degree Arctan2(float y, float x)
{
	return ToDegree(atan2f(y, x));
}

//Define Template Functions
template<typename T>
inline T Clamp(T value, T min, T max)
{
	return Max(Min(value, max), min);
}

template<typename T>
inline T Wrap(T value, T min, T max)
{
	T n = fmodf(value - min, max - min);
	return (n >= 0) ? (n + min) : (n + max);
}
template<>
inline int Wrap(int value, int min, int max)
{
	int n = (value - min) % (max - min);
	return (n >= 0) ? (n + min) : (n + max);
}
template<typename T>
inline void Swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}
template<typename T>
inline T Abs(T a)
{
	return a > static_cast<T>(0) ? a : -a;
}


template<typename T>
inline const T& Max(const T& a, const T& b)
{
	return std::max(a, b);
}

template<typename T>
inline const T& Min(const T& a, const T& b)
{
	return std::min(a, b);
}

template<typename T>
inline T Sign(T value)
{
	value < static_cast<T>(0) ? static_cast<T>(-1) : static_cast<T>(1);
}

inline Size2F::Size2F(void)
	:D2D1_SIZE_F(D2D1::SizeF(0.f, 0.f))
{

}

inline Size2F::Size2F(float width, float height)
	: D2D1_SIZE_F(D2D1::SizeF(width, height))
{
}

inline Size2F Size2F::operator +(const Size2F &s) const
{
	return Size2F(width + s.width, height + s.height);
}

inline Size2F Size2F::operator -(const Size2F &s) const
{
	return Size2F(width - s.width, height - s.height);
}

inline Size2F Size2F::operator /(const Size2F &s) const
{
	return Size2F(width / s.width, height / s.height);
}

inline Size2F Size2F::operator *(const Size2F &s) const
{
	return Size2F(width * s.width, height * s.height);
}

inline Size2F Size2F::operator -(void) const
{
	return Size2F(-width, -height);
}


inline Size2F& Size2F::operator +=(const Size2F &s)
{
	width += s.width;
	height += s.height;
	return *this;
}

inline Size2F& Size2F::operator -=(const Size2F &s)
{
	width -= s.width;
	height -= s.height;
	return *this;
}

inline Size2F& Size2F::operator /=(const Size2F &s)
{
	width /= s.width;
	height /= s.height;
	return *this;
}

inline Size2F& Size2F::operator *=(const Size2F &s)
{
	width *= s.width;
	height *= s.height;
	return *this;
}

inline bool Size2F::operator ==(const Size2F &s) const
{
	return ((width == s.width) && (height == s.height));
}

inline bool Size2F::operator !=(const Size2F &s) const
{
	return ((width != s.width) || (height != s.height));
}

inline void Size2F::Set(const Size2F &s)
{
	*this = s;
}
inline void Size2F::Set(float width, float height)
{
	this->width = width;
	this->height = height;
}

inline Size2U::Size2U()
	:D2D1_SIZE_U(D2D1::SizeU(0, 0))
{
}

inline Size2U::Size2U(unsigned int width, unsigned int height)
	: D2D1_SIZE_U(D2D1::SizeU(width, height))
{
}

inline Size2U Size2U::operator +(const Size2U &s) const
{
	return Size2U(width + s.width, height + s.height);
}

inline Size2U Size2U::operator -(const Size2U &s) const
{
	return Size2U(width - s.width, height - s.height);
}

inline Size2U Size2U::operator /(const Size2U &s) const
{
	return Size2U(width / s.width, height / s.height);
}

inline Size2U Size2U::operator *(const Size2U &s) const
{
	return Size2U(width * s.width, height * s.height);
}

inline Size2U& Size2U::operator +=(const Size2U &s)
{
	width += s.width;
	height += s.height;
	return *this;
}

inline Size2U& Size2U::operator -=(const Size2U &s)
{
	width -= s.width;
	height -= s.height;
	return *this;
}

inline Size2U& Size2U::operator /=(const Size2U &s)
{
	width /= s.width;
	height /= s.height;
	return *this;
}

inline Size2U& Size2U::operator *=(const Size2U &s)
{
	width *= s.width;
	height *= s.height;
	return *this;
}

inline bool Size2U::operator ==(const Size2U &s) const
{
	return ((width == s.width) && (height == s.height));
}

inline bool Size2U::operator !=(const Size2U &s) const
{
	return ((width != s.width) || (height != s.height));
}

inline void Size2U::Set(const Size2U &s)
{
	*this = s;
}
inline void Size2U::Set(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
}

inline Vec2F::Vec2F(void)
	:D2D1_POINT_2F(D2D1::Point2F(0.f, 0.f))
{
}

inline Vec2F::Vec2F(float x, float y)
	: D2D1_POINT_2F(D2D1::Point2F(x, y))
{
}

inline Vec2F::operator float*(void)
{
	return &x;
}

inline Vec2F::operator const float*(void) const
{
	return const_cast<const float*>(&x);
}



inline Vec2F Vec2F::operator +(const Vec2F &v) const
{
	return Vec2F(x + v.x, y + v.y);
}

inline Vec2F Vec2F::operator -(const Vec2F &v) const
{
	return Vec2F(x - v.x, y - v.y);
}

inline Vec2F Vec2F::operator /(const Vec2F &v) const
{
	return Vec2F(x / v.x, y / v.y);
}

inline Vec2F Vec2F::operator *(const Vec2F &v) const
{
	return Vec2F(x * v.x, y * v.y);
}

inline Vec2F Vec2F::operator *(float f) const
{
	return Vec2F(x * f, y * f);
}

inline Vec2F Vec2F::operator /(float f) const
{
	float inv = 1.0f / f;
	return Vec2F(x * inv, y * inv);
}

inline Vec2F Vec2F::operator -(void) const
{
	return Vec2F(-x, -y);
}


inline Vec2F& Vec2F::operator +=(const Vec2F &v)
{
	x += v.x;
	y += v.y;
	return *this;
}

inline Vec2F& Vec2F::operator -=(const Vec2F &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

inline Vec2F& Vec2F::operator /=(const Vec2F &v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

inline Vec2F& Vec2F::operator *=(const Vec2F &v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

inline Vec2F& Vec2F::operator *=(float f)
{
	x *= f;
	y *= f;
	return *this;
}

inline Vec2F& Vec2F::operator /=(float f)
{
	float inv = 1.0f / f;
	x *= inv;
	y *= inv;
	return *this;
}

inline bool Vec2F::operator ==(const Vec2F &v) const
{
	return ((x == v.x) && (y == v.y));
}

inline bool Vec2F::operator !=(const Vec2F &v) const
{
	return ((x != v.x) || (y != v.y));
}

inline float Vec2F::Dot(const Vec2F &b)
{
	return x * b.x + y * b.y;
}
inline float Vec2F::Cross(const Vec2F &a, const Vec2F &b)
{
	return a.x * b.y - a.y * b.x;
}
inline Vec2F Vec2F::Cross(const Vec2F &a, float s)
{
	return Vec2F(s * a.y, -s * a.x);
}
inline Vec2F Vec2F::Cross(float s, const Vec2F &a)
{
	return Vec2F(-s * a.y, s * a.x);
}

inline Vec2F Vec2F::Normalize()
{
	return *this / Size();
}

inline Degree Vec2F::Angle() const
{
	return ToDegree(atan2f(this->y, this->x));
}

inline Degree Vec2F::Angle(const Vec2F& v) const
{
	return ToDegree(atan2f(v.y - this->y, v.x - this->x));
}

inline float Vec2F::DistanceSquare(const Vec2F& v) const
{
	Vec2F d = *this - v;
	return (d.x * d.x) + (d.y * d.y);
}

inline float Vec2F::Size()
{
	return Distance(Vec2F(0.f,0.f));
}

inline float Vec2F::Distance(const Vec2F& v) const
{
	return sqrt(DistanceSquare(v));
}



inline void Vec2F::Transform(float x, float y)
{
	this->x += x;
	this->y += y;
}

inline void Vec2F::Transform(const Vec2F &v)
{
	*this += v;
}

inline void Vec2F::Set(const Vec2F &v)
{
	*this = v;
}
inline void Vec2F::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}

inline Vec2F operator *(float f, const Vec2F &v)
{
	return v * f;
}
inline float Distance(const Vec2F& a, const Vec2F& b)
{
	return sqrtf(DistanceSquare(a, b));
}

inline float DistanceSquare(const Vec2F& a, const Vec2F& b)
{
	Vec2F d = b - a;
	return (d.x * d.x) + (d.y * d.y);
}

inline Degree Angle(const Vec2F& a, const Vec2F& b)
{
	return Arctan2(b.y - a.y, b.x - a.x);
}

inline Vec2L::Vec2L(void)
	:D2D1_POINT_2L(D2D1::Point2L(0, 0))
{

}

inline Vec2L::Vec2L(long x, long y)
	: D2D1_POINT_2L(D2D1::Point2L(x, y))
{
}

inline Vec2L::operator long*(void)
{
	return &x;
}

inline Vec2L::operator const long*(void) const
{
	return const_cast<const long*>(&x);
}



inline Vec2L Vec2L::operator +(const Vec2L &v) const
{
	return Vec2L(x + v.x, y + v.y);
}

inline Vec2L Vec2L::operator -(const Vec2L &v) const
{
	return Vec2L(x - v.x, y - v.y);
}

inline Vec2L Vec2L::operator /(const Vec2L &v) const
{
	return Vec2L(x / v.x, y / v.y);
}

inline Vec2L Vec2L::operator *(const Vec2L &v) const
{
	return Vec2L(x * v.x, y * v.y);
}

inline Vec2L Vec2L::operator *(long l) const
{
	return Vec2L(x * l, y * l);
}

inline Vec2L Vec2L::operator /(long l) const
{
	long inv = 1 / l;
	return Vec2L(x * inv, y * inv);
}

inline Vec2L Vec2L::operator -(void) const
{
	return Vec2L(-x, -y);
}



inline Vec2L& Vec2L::operator +=(const Vec2L &v)
{
	x += v.x;
	y += v.y;
	return *this;
}

inline Vec2L& Vec2L::operator -=(const Vec2L &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

inline Vec2L& Vec2L::operator /=(const Vec2L &v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

inline Vec2L& Vec2L::operator *=(const Vec2L &v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

inline Vec2L& Vec2L::operator *=(long f)
{
	x *= f;
	y *= f;
	return *this;
}

inline Vec2L& Vec2L::operator /=(long l)
{
	long inv = 1 / l;
	x *= inv;
	y *= inv;
	return *this;
}

inline bool Vec2L::operator ==(const Vec2L &v) const
{
	return ((x == v.x) && (y == v.y));
}

inline bool Vec2L::operator !=(const Vec2L &v) const
{
	return ((x != v.x) || (y != v.y));
}

inline float Vec2L::Dot(const Vec2L &b)
{
	return x * b.x + y * b.y;
}
inline float Vec2L::Cross(const Vec2L &a, const Vec2L &b)
{
	return a.x * b.y - a.y * b.x;
}
inline Vec2L Vec2L::Cross(const Vec2L &a, long s)
{
	return Vec2L(s * a.y, -s * a.x);
}
inline Vec2L Vec2L::Cross(long s, const Vec2L &a)
{
	return Vec2L(-s * a.y, s * a.x);
}
inline Vec2L Vec2L::Normalize()
{
	return *this / Size();
}
inline Degree Vec2L::Angle() const
{
	return ToDegree(atan2f(this->y, this->x));
}

inline Degree Vec2L::Angle(const Vec2L& v) const
{
	return ToDegree(atan2f(v.y - this->y, v.x - this->x));
}

inline float Vec2L::DistanceSquare(const Vec2L & v) const
{
	Vec2L d = *this - v;
	return (d.x * d.x) + (d.y * d.y);
}

inline float Vec2L::Size()
{
	return Distance(Vec2L(0, 0));
}

inline float Vec2L::Distance(const Vec2L& v) const
{
	return sqrt(DistanceSquare(v));
}


inline void Vec2L::Transform(long x, long y)
{
	this->x += x;
	this->y += y;
}

inline void Vec2L::Transform(const Vec2L &v)
{
	*this += v;
}

inline void Vec2L::Set(const Vec2L &v)
{
	*this = v;
}
inline void Vec2L::Set(long x, long y)
{
	this->x = x;
	this->y = y;
}

inline Vec2L operator *(long l, const Vec2L &v)
{
	return v * l;
}

inline float Distance(const Vec2L& a, const Vec2L& b)
{
	return sqrtf(DistanceSquare(a, b));
}

inline float DistanceSquare(const Vec2L& a, const Vec2L& b)
{
	Vec2L d = b - a;
	return (d.x * d.x) + (d.y * d.y);
}

inline Degree Angle(const Vec2L& a, const Vec2L& b)
{
	return Arctan2(b.y - a.y, b.x - a.x);
}

inline Color::Color(void)
	:D2D1_COLOR_F(D2D1::ColorF(0.f, 0.f, 0.f, 1.f))
{}

inline Color::Color(ColorType color)
	: D2D1_COLOR_F(D2D1::ColorF(color))
{
}

inline Color::Color(float r, float g, float b)
	: D2D1_COLOR_F(D2D1::ColorF(r, g, b, 1.f))
{}

inline Color::Color(float r, float g, float b, float a)
	: D2D1_COLOR_F(D2D1::ColorF(r, g, b, a))
{}

inline Color::Color(ARGB ulcolor)
{
	float div = 1.0f / 255.0f;
	r = div * (float)(unsigned char)(ulcolor >> 16);
	g = div * (float)(unsigned char)(ulcolor >> 8);
	b = div * (float)(unsigned char)ulcolor;
	a = div * (float)(unsigned char)(ulcolor >> 24);
}

inline Color::operator ARGB(void) const
{
	ARGB dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (ARGB)(r * 255.0f + 0.5f);
	ARGB dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (ARGB)(g * 255.0f + 0.5f);
	ARGB dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (ARGB)(b * 255.0f + 0.5f);
	ARGB dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (ARGB)(a * 255.0f + 0.5f);

	return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}

inline Color Color::operator +(const Color &c) const
{
	return Color(r + c.r, g + c.g, b + c.b, a + c.a);
}

inline Color Color::operator -(const Color &c) const
{
	return Color(r - c.r, g - c.g, b - c.b, a - c.a);
}

inline Color Color::operator /(const Color &c) const
{
	return Color(r / c.r, g / c.g, b / c.b, a / c.a);
}

inline Color Color::operator *(const Color &c) const
{
	return Color(r * c.r, g * c.g, b * c.b, a * c.a);
}

inline Color Color::operator +(float f) const
{
	return Color(r + f, g + f, b + f, a + f);
}

inline Color Color::operator -(float f) const
{
	return Color(r - f, g - f, b - f, a - f);
}

inline Color Color::operator /(float f) const
{
	float inv = 1.0f / f;
	return Color(r * f, g * f, b * f, a * f);
}

inline Color Color::operator *(float f) const
{
	return Color(r * f, g * f, b * f, a * f);
}

inline Color& Color::operator +=(const Color &c)
{
	r += c.r;
	g += c.g;
	b += c.b;
	a += c.a;
	return *this;
}

inline Color& Color::operator -=(const Color &c)
{
	r -= c.r;
	g -= c.g;
	b -= c.b;
	a -= c.a;
	return *this;
}

inline Color& Color::operator /=(const Color &c)
{
	r /= c.r;
	g /= c.g;
	b /= c.b;
	a /= c.a;
	return *this;
}

inline Color& Color::operator *=(const Color &c)
{
	r *= c.r;
	g *= c.g;
	b *= c.b;
	a *= c.a;
	return *this;
}

inline Color& Color::operator +=(float f)
{
	r += f;
	g += f;
	b += f;
	a += f;
	return *this;
}

inline Color& Color::operator -=(float f)
{
	r -= f;
	g -= f;
	b -= f;
	a -= f;
	return *this;
}

inline Color& Color::operator /=(float f)
{
	float inv = 1.0f / f;
	r *= inv;
	g *= inv;
	b *= inv;
	a *= inv;
	return *this;
}

inline Color& Color::operator *=(float f)
{
	r *= f;
	g *= f;
	b *= f;
	a *= f;
	return *this;
}

inline Color& Color::operator =(ARGB ulcolor)
{
	float div = 1.0f / 255.0f;
	a = div * (float)(unsigned char)(ulcolor >> 24);
	r = div * (float)(unsigned char)(ulcolor >> 16);
	g = div * (float)(unsigned char)(ulcolor >> 8);
	b = div * (float)(unsigned char)(ulcolor >> 0);
	return *this;
}

inline bool Color::operator ==(const Color &c) const
{
	return r == c.r && g == c.g && b == c.b && a == c.a;
}

inline bool Color::operator ==(ARGB ulcolor) const
{
	return
		(unsigned char)(a * 255.0f) == (unsigned char)(ulcolor >> 24) &&
		(unsigned char)(r * 255.0f) == (unsigned char)(ulcolor >> 16) &&
		(unsigned char)(g * 255.0f) == (unsigned char)(ulcolor >> 8) &&
		(unsigned char)(b * 255.0f) == (unsigned char)(ulcolor >> 0);
}

inline bool Color::operator !=(const Color &c) const
{
	return r != c.r || g != c.g || b != c.b || a != c.a;
}

inline bool Color::operator !=(ARGB ulcolor) const
{
	return
		(unsigned char)(a * 255.0f) != (unsigned char)(ulcolor >> 24) ||
		(unsigned char)(r * 255.0f) != (unsigned char)(ulcolor >> 16) ||
		(unsigned char)(g * 255.0f) != (unsigned char)(ulcolor >> 8) ||
		(unsigned char)(b * 255.0f) != (unsigned char)(ulcolor >> 0);
}

inline void Color::Set(const Color &c)
{
	a = c.a;
	r = c.r;
	g = c.g;
	b = c.b;
}
inline void Color::Set(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}
inline void Color::Set(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

inline void Color::Set(ARGB ulcolor)
{
	float div = 1.0f / 255.0f;
	a = div * (float)(unsigned char)(ulcolor >> 24);
	r = div * (float)(unsigned char)(ulcolor >> 16);
	g = div * (float)(unsigned char)(ulcolor >> 8);
	b = div * (float)(unsigned char)(ulcolor >> 0);
}


inline ARGB COLOR_RGBA(int r, int g, int b, int a)
{
	return (ARGB)(((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}
inline ARGB COLOR_RGB(int r, int g, int b)
{
	return COLOR_RGBA(0xff, r, g, b);
}
inline Color operator +(float f, const Color &c)
{
	return c + f;
}
inline Color operator *(float f, const Color &c)
{
	return c * f;
}
inline bool operator ==(ARGB ulcolor, const Color &c)
{
	return c == ulcolor;
}
inline bool operator !=(ARGB ulcolor, const Color &c)
{
	return c != ulcolor;
}

inline Rect::Rect()
	:D2D1_RECT_F(D2D1::RectF())
{

}
inline Rect::Rect(float left, float top, float right, float bottom)
	: D2D1_RECT_F(D2D1::RectF(left, top, right, bottom))
{

}
inline Rect::Rect(const Vec2F& lt, const Vec2F& rb)
	:D2D1_RECT_F(D2D1::RectF(lt.x, lt.y, rb.x, rb.y))
{

}

inline bool Rect::operator==(const Rect & other) const
{
	return left == other.left&&
		right == other.right&&
		top == other.top&&
		bottom == other.bottom;
}

inline bool Rect::operator!=(const Rect & other) const
{
	return left != other.left ||
		right != other.right ||
		top != other.top ||
		bottom != other.bottom;
	
}


inline float Rect::GetCenterX() const
{
	return (right + left)/2;
}
inline float Rect::GetCenterY() const
{
	return (bottom + top)/2;
}
inline Vec2F Rect::GetCenter() const
{
	return Vec2F(GetCenterX(), GetCenterY());
}
inline Vec2F Rect::GetPos(CritRectPos p) const
{
	if (p == CENTER)
		return GetCenter();
	else if (p == LEFT_TOP)
		return Vec2F(left, top);
	else if (p == CENTER_TOP)
		return Vec2F(GetCenterX(), top);
	else if (p == RIGHT_TOP)
		return Vec2F(right, top);

	else if (p == LEFT_CENTER)
		return Vec2F(left, GetCenterY());
	else if (p == RIGHT_CENTER)
		return Vec2F(right,GetCenterY());

	else if (p == LEFT_BOTTOM)
		return Vec2F(left, bottom);
	else if (p == CENTER_TOP)
		return Vec2F(GetCenterX(), bottom);
	else if (p == RIGHT_TOP)
		return Vec2F(right,bottom);
}
inline float Rect::GetWidth() const
{
	return right - left;
}
inline float Rect::GetHeight() const
{
	return bottom - top;
}
inline Rect Rect::Offset(const Vec2F& offset) const
{
	Rect r = *this;
	r.left += offset.x;
	r.right += offset.x;
	r.top += offset.y;
	r.bottom += offset.y;
	return r;
}
inline bool Rect::IsIntersect(const Rect& other) const
{
	if (right < other.left ||
		bottom < other.top ||
		left > other.right ||
		top > other.bottom)
	{
		return false;
	}
		
	return true;
}

inline bool Rect::IsIntersect(const Vec2F & other) const
{
	if (left < other.x &&
		top < other.y &&
		right > other.x &&
		bottom > other.y)
		return true;
	return false;
}

inline bool Rect::IsIntersect(const Vec2L & other) const
{
	if (left < other.x &&
		top < other.y &&
		right > other.x &&
		bottom > other.y)
		return true;
	return false;
}


inline Rect Rect::GetIntersection(const Rect& other) const
{
	//°ãÄ¡Áö ¾ÊÀ¸¸é
	if ((left > other.right) || 
		(right < other.left) || 
		(top > other.bottom) ||
		(bottom < other.top)) 
		return Rect();

	//°ãÄ¡¸é
	Rect r;
	r.left=	Max(left, other.left);
	r.top = Max(top, other.top);
	r.right = Min(right, other.right);
	r.bottom = Min(bottom, other.bottom);

	return r;
}

inline void  Rect::Set(const Rect& other)
{
	left = other.left;
	right = other.right;
	top = other.top;
	bottom = other.bottom;
}
inline void  Rect::Set(float left, float top, float right, float bottom)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}
inline void  Rect::Set(const Vec2F& lt, const Vec2F& rb)
{
	left = lt.x;
	top = lt.y;
	right = rb.x;
	bottom = rb.y;
}

inline Circle::Circle(const Vec2F& center, float radius)
	:center(center), radius(radius)
{

}
inline Circle::~Circle()
{

}
inline Circle Circle::Offset(const Vec2F& offset) const
{
	return Circle(center + offset, radius);
}