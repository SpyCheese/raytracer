#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "Object.h"
#include "Functions.h"

// Sphere - объект, сфера
// Задаётся центром и радиусом

struct Sphere : Object {
	Vector3 center;
	double radius;
	Material * material;

	Sphere(Vector3 const & p, double r, Material * m) :
		center(p), radius(r), material(m) {}

	double getCrossT(Vector3 const & pos, Vector3 const & dir) {
		// pos + dir*t лежит на сфере
		// dist(pos + dir*t, center) == radius
		// (pos-center + dir*t)^2 == radius^2
		// dir^2 * t^2  +  2*(pos-center)*dir * t  +  (pos-center)^2-radius^2   ==   0
		// dir^2 == 1, так как вектор длины 1
		// Квадратное уравнение
		double b2 = dot(pos - center, dir);
		double c = length2(pos-center) - radius*radius;
		double d = b2*b2 - c;
		if (d < 0.0)
			return INF;
		double ds = sqrt(d);
		double t1 = -b2 - ds;
		double t2 = -b2 + ds;
		if (t2 < EPS)
			return INF;
		if (t1 < EPS)
			return t2;
		return t1;
	}

	virtual Color getColor(Vector3 const & pos, Vector3 const & dir) {
		return getMaterialColor(material, pos, dir, normalize(pos - center));
	}
};

#endif
