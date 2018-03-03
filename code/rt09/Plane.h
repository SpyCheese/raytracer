#ifndef __PLANE_H__
#define __PLANE_H__
#include "Object.h"
#include "Functions.h"

// Plane - объект, бесконечная плоскость
// Задаётся точкой и перпендикуляром

struct Plane : Object {
	Vector3 point, normal;
	Material * material;

	Plane(Vector3 const & p, Vector3 const & n, Material * m) :
		point(p), normal(normalize(n)), material(m) {}

	double getCrossT(Vector3 const & pos, Vector3 const & dir) {
		// pos + dir*t лежит в плоскости
		// dot(pos + dir*t - point, normal) == 0
		// dot(pos - point, normal) = -dot(dir, normal)*t
		double t = -dot(pos - point, normal) / dot(dir, normal);
		return t > EPS ? t : INF;
	}

	virtual Color getColor(Vector3 const & pos, Vector3 const & dir) {
		return getMaterialColor(material, pos, dir, normal);
	}

	virtual void handleLightRay(Vector3 const & pos, Vector3 const & dir, Color const& col) {
        materialHandleLightRay(material, pos, dir, normal, col);
    }
};

#endif
