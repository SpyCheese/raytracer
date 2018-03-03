#ifndef __L_SPHERE_H__
#define __L_SPHERE_H__
#include "Object.h"
#include "Functions.h"

// L_Sphere - объект, сфера
// Задаётся центром и радиусом
// На этапе трассировки световых лучей запоминает, какой свет на неё попал.

struct L_Sphere : Object {
	Vector3 center;
	double radius;
	Material * material;

    int nx;
    vector < vector < Color > > light;
    double lightK;

	L_Sphere(Vector3 const & p, double r, Material * m, double step) :
		center(p), radius(r), material(m),
        nx(PI*r / step), light(nx), lightK(LIGHT_STEP*LIGHT_STEP/(step*step)) {
        for (int i = 0; i < nx; ++i) {
            double ang = (i + 0.5) * PI / nx;
            double r1 = r*sin(ang);
            light[i].resize(2*PI*r1 / step);
        }
    }

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
        Vector3 n = normalize(pos - center);
        int x = max(0, min(nx - 1, int(acos(n.z) / PI * nx)));
        int ny = (int)light[x].size();
        int y = max(0, min(ny - 1, int((atan2(n.y, n.x) + PI) / (2.0*PI) * ny)));
		return getMaterialColor(material, pos, dir, n) + light[x][y];
	}

	virtual void handleLightRay(Vector3 const & pos, Vector3 const & dir, Color const& col) {
        Vector3 n = normalize(pos - center);
        int x = max(0, min(nx - 1, int(acos(n.z) / PI * nx)));
        int ny = (int)light[x].size();
        int y = max(0, min(ny - 1, int((atan2(n.y, n.x) + PI) / (2.0*PI) * ny)));
        light[x][y] += materialHandleLightRay(material, pos, dir, n, col) * lightK;
    }
};

#endif
