#ifndef __L_CAP_H__
#define __L_CAP_H__
#include "Object.h"
#include "Functions.h"

// L_Cap - объект, сферический сегмент (усечённая сфера)
// Задаётся центром, радиусом, направлением, углом
// На этапе трассировки световых лучей запоминает, какой свет на неё попал.

struct L_Cap : Object {
	Vector3 center;
	double radius;
	Vector3 v;
	double angle, rcosA;
	Material * material;

    int nx;
    vector < vector < Color > > light;
    double lightK;
    Vector3 dir1, dir2;

	L_Cap(Vector3 const & p, double r, Vector3 const & v, double a, Material * m, double step) :
		center(p), radius(r), v(normalize(v)), angle(a), rcosA(r*cos(a)), material(m),
        nx(a*r / step), light(nx), lightK(LIGHT_STEP*LIGHT_STEP/(step*step)),
        dir1(getAnyNormal(v)), dir2(cross(dir1, v)) {
        for (int i = 0; i < nx; ++i) {
            double ang = (i + 0.5) * angle / nx;
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
        Vector3 n = normalize(pos - center);
        int x = max(0, min(nx - 1, int(acos(dot(v, n)) / angle * nx)));
        int ny = (int)light[x].size();
        int y = max(0, min(ny - 1, int((atan2(dot(n, dir1), dot(n, dir2)) + PI) / (2.0*PI) * ny)));
		return getMaterialColor(material, pos, dir, n) + light[x][y];
	}

	virtual void handleLightRay(Vector3 const & pos, Vector3 const & dir, Color const& col) {
        Vector3 n = normalize(pos - center);
        int x = max(0, min(nx - 1, int(acos(dot(v, n)) / angle * nx)));
        int ny = (int)light[x].size();
        int y = max(0, min(ny - 1, int((atan2(dot(n, dir1), dot(n, dir2)) + PI) / (2.0*PI) * ny)));
        light[x][y] += materialHandleLightRay(material, pos, dir, n, col) * lightK;
    }
};

#endif
