#ifndef __CAP_H__
#define __CAP_H__
#include "Object.h"
#include "Functions.h"

// Cap - объект, сферический сегмент (усечённая сфера)
// Задаётся центром, радиусом, направлением, углом

struct Cap : Object {
	Vector3 center;
	double radius;
	Vector3 v;
	double rcosA;
	Material * material;

	Cap(Vector3 const & p, double r, Vector3 const & v, double a, Material * m) :
		center(p), radius(r), v(normalize(v)), rcosA(r*cos(a)), material(m) {}

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
		if (t1 > EPS) {
			double w = dot(pos - center + dir*t1, v);
			if (w >= rcosA)
				return t1;
		}
		if (t2 > EPS) {
			double w = dot(pos - center + dir*t2, v);
			if (w >= rcosA)
				return t2;
		}
		return INF;
	}

	virtual Color getColor(Vector3 const & pos, Vector3 const & dir) {
		return getMaterialColor(material, pos, dir, normalize(pos - center));
	}

	virtual void handleLightRay(Vector3 const & pos, Vector3 const & dir, Color const& col) {
        materialHandleLightRay(material, pos, dir, normalize(pos - center), col);
    }
};

#endif
