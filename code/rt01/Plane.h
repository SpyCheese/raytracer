#ifndef __PLANE_H__
#define __PLANE_H__
#include "Object.h"

// Plane - объект, бесконечная плоскость
// Задаётся точкой и перпендикуляром, а также цветом

struct Plane : Object {
	Vector3 point, normal;
	Color color;

	Plane(Vector3 const & p, Vector3 const & n, Color const & c) :
		point(p), normal(normalize(n)), color(c) {}

	double getCrossT(Vector3 const & pos, Vector3 const & dir) {
		// pos + dir*t лежит в плоскости
		// dot(pos + dir*t - point, normal) == 0
		// dot(pos - point, normal) = -dot(dir, normal)*t
		double t = -dot(pos - point, normal) / dot(dir, normal);
		return t > EPS ? t : INF;
	}

	virtual Color getColor(Vector3 const & pos, Vector3 const & dir) {
		return color;
	}
};

#endif
