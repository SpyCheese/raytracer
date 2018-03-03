#ifndef __VECTOR_H__
#define __VECTOR_H__
#include "Common.h"
// Vector3 - тип, хранящий трёхмерный. Операции над векторами:
// Сложение, вычитание
// Умножение и деление на число
// Скалярное и векторное произведение
// Длина, квадрат длины, нормализация

struct Vector3 {
	double x, y, z;
	
	Vector3() : x(0.0), y(0.0), z(0.0) {}
	Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

	Vector3 & operator += (Vector3 const & b) { x+=b.x; y+=b.y; z+=b.z; return *this; }
	Vector3 & operator -= (Vector3 const & b) { x-=b.x; y-=b.y; z-=b.z; return *this; }
	Vector3 & operator *= (double b) { x*=b; y*=b; z*=b; return *this; }
	Vector3 & operator /= (double b) { x/=b; y/=b; z*=b; return *this; }
};

inline Vector3 operator + (Vector3 const & a, Vector3 const & b) { return Vector3(a.x+b.x, a.y+b.y, a.z+b.z); }
inline Vector3 operator - (Vector3 const & a, Vector3 const & b) { return Vector3(a.x-b.x, a.y-b.y, a.z-b.z); }
inline Vector3 operator - (Vector3 const & a) { return Vector3(-a.x, -a.y, -a.z); }
inline Vector3 operator * (Vector3 const & a, double b) { return Vector3(a.x*b, a.y*b, a.z*b); }
inline Vector3 operator / (Vector3 const & a, double b) { return Vector3(a.x/b, a.y/b, a.z/b); }
inline Vector3 operator * (double b, Vector3 const & a) { return Vector3(a.x*b, a.y*b, a.z*b); }
inline Vector3 operator / (double b, Vector3 const & a) { return Vector3(a.x/b, a.y/b, a.z/b); }

inline double dot(Vector3 const & a, Vector3 const & b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
inline Vector3 cross(Vector3 const& a, Vector3 const & b) {
	return Vector3(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
	);
}
inline double length2(const Vector3 & a) { return a.x*a.x + a.y*a.y + a.z*a.z; }
inline double length(const Vector3 & a) { return sqrt(a.x*a.x + a.y*a.y + a.z*a.z); }
inline Vector3 normalize(const Vector3 & a) { return a / sqrt(a.x*a.x + a.y*a.y + a.z*a.z); }

inline Vector3 getAnyNormal(Vector3 const& a) {
	Vector3 b1 = Vector3(1.0, 0.0, 0.0) - a * (a.x / length2(a));
	Vector3 b2 = Vector3(0.0, 1.0, 0.0) - a * (a.y / length2(a));
    if (length2(b1) > length2(b2))
        return normalize(b1);
    else
        return normalize(b2);
}


#endif
