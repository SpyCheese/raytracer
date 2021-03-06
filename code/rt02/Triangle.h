#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "Object.h"

// Triangle - объект, треугольник

struct Triangle : Object {
	// Вершины имеют координаты p1, p1+v1, p1+v2
	Vector3 p1, v1, v2;
	Vector3 normal;
	Color color;

	Triangle(Vector3 const & p1, Vector3 const & p2, Vector3 const & p3, Color const & c) :
		p1(p1), v1(p2-p1), v2(p3-p1), normal(normalize(cross(v1, v2))), color(c) {}

	double getCrossT(Vector3 const & pos, Vector3 const & dir) {
		// pos + dir*t лежит в плоскости треугольника
		// dot(pos + dir*t - p1, normal) == 0
		// dot(pos - p1, normal) = -dot(dir, normal)*t
		double t = -dot(pos - p1, normal) / dot(dir, normal);
		if (t < EPS)
			return INF;
		Vector3 v = pos + dir*t - p1;
		// Найдём такие a1 и a2, что v == v1*a1 + v2*a2
		// v*v1 == v1*v1*a1 + v1*v2*a2
		// v*v2 == v1*v2*a1 + v2*v2*a2
		// Сисема из двух линейных уравнений, решается:
		double b11 = length2(v1), b12 = dot(v1, v2), c1 = dot(v, v1);
		double b21 = dot(v1, v2), b22 = length2(v2), c2 = dot(v, v2);
		double det = b11*b22 - b12*b21;
		double a1 = (c1*b22 - c2*b12) / det;
		double a2 = (b11*c2 - c1*b21) / det;
		return a1 >= 0.0 && a2 >= 0.0 && a1 + a2 <= 1.0 ? t : INF;
	}

	virtual Color getColor(Vector3 const & pos, Vector3 const & dir) {
		return color;
	}
};

#endif
