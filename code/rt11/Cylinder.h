#ifndef __CYLINDER_H__
#define __CYLINDER_H__
#include "Object.h"
#include "Functions.h"

// Cylinder - объект, боковая повержность цилиндра

struct Cylinder : Object {
	Vector3 p, v;
	double r, h;
	Material * material;

	// Задаётся центрами оснований и радиусом
	Cylinder(Vector3 const & p1, Vector3 const & p2, double r, Material * m) :
		p(p1), v(normalize(p2 - p1)), r(r), h(length(p2 - p1)), material(m) {}

	double getCrossT(Vector3 const & pos, Vector3 const & dir) {
		Vector3 p1 = pos - p;
		p1 -= v*dot(v, p1);
		Vector3 d1 = dir - v*dot(v, dir);
		if (length2(d1) < EPS*EPS)
			return INF;
		// p1 + d1*t лежит на цилиндре
		// (p1 + d1*t)^2 == r^2
		// d1^2 * t^2  +  2*p1*d1 * t  +  p1^2-r^2   ==   0
		// Квадратное уравнение
		double a = length2(d1);
		double b2 = dot(p1, d1);
		double c = length2(p1) - r*r;
		double d = b2*b2 - a*c;
		if (d < 0.0)
			return INF;
		double ds = sqrt(d);
		double t1 = (-b2 - ds) / a;
		double t2 = (-b2 + ds) / a;
		if (t1 > EPS) {
			double w = dot(pos + dir*t1 - p, v);
			if (0 <= w && w <= h)
				return t1;
		}
		if (t2 > EPS) {
			double w = dot(pos + dir*t2 - p, v);
			if (0 <= w && w <= h)
				return t2;
		}
		return INF;
	}

	Color getColor(Vector3 const & pos, Vector3 const & dir) {
		Vector3 n = pos - p;
		n -= dot(n, v)*v;
		return getMaterialColor(material, pos, dir, normalize(n));
	}

	virtual void handleLightRay(Vector3 const & pos, Vector3 const & dir, Color const& col) {
		Vector3 n = pos - p;
		n -= dot(n, v)*v;
        materialHandleLightRay(material, pos, dir, normalize(n), col);
    }
};

#endif
