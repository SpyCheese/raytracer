#ifndef __L_PARALLELOGRAM_H__
#define __L_PARALLELOGRAM_H__
#include "Object.h"
#include "Functions.h"

// L_Parallelogram - объект, параллелограмм
// На этапе трассировки световых лучей запоминает, какой свет на него попал.

struct L_Parallelogram : Object {
	// Вершины имеют координаты p1, p1+v1, p1+v1+v2, p1+v2
	Vector3 p1, v1, v2;
	Vector3 normal;
	Material * material;
    int nx, ny;
    vector < vector < Color > > light;
    double lightK;

	// Задаётся тремя последовательными вершинами
	L_Parallelogram(Vector3 const & p1, Vector3 const & p2, Vector3 const & p3, Material * m, double step) :
		p1(p1), v1(p2-p1), v2(p3-p2), normal(normalize(cross(v1, v2))), material(m),
        nx(length(v1) / step), ny(length(v2) / step), light(nx, vector<Color>(ny)), lightK(LIGHT_STEP*LIGHT_STEP/(step*step))
    {}

	double getCrossT(Vector3 const & pos, Vector3 const & dir) {
		// pos + dir*t лежит в плоскости
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
		return a1 >= 0.0 && a2 >= 0.0 && a1 <= 1.0 && a2 <= 1.0 ? t : INF;
	}

	virtual Color getColor(Vector3 const & pos, Vector3 const & dir) {
		Vector3 v = pos - p1;
		double b11 = length2(v1), b12 = dot(v1, v2), c1 = dot(v, v1);
		double b21 = dot(v1, v2), b22 = length2(v2), c2 = dot(v, v2);
		double det = b11*b22 - b12*b21;
		double a1 = (c1*b22 - c2*b12) / det;
		double a2 = (b11*c2 - c1*b21) / det;
        int x = max(0, min(nx - 1, (int)(a1*nx)));
        int y = max(0, min(ny - 1, (int)(a2*ny)));
		return getMaterialColor(material, pos, dir, normal) + light[x][y];
	}

	virtual void handleLightRay(Vector3 const & pos, Vector3 const & dir, Color const& col) {
		Vector3 v = pos - p1;
		double b11 = length2(v1), b12 = dot(v1, v2), c1 = dot(v, v1);
		double b21 = dot(v1, v2), b22 = length2(v2), c2 = dot(v, v2);
		double det = b11*b22 - b12*b21;
		double a1 = (c1*b22 - c2*b12) / det;
		double a2 = (b11*c2 - c1*b21) / det;
        int x = max(0, min(nx - 1, (int)(a1*nx)));
        int y = max(0, min(ny - 1, (int)(a2*ny)));
        light[x][y] += materialHandleLightRay(material, pos, dir, normal, col) * lightK;
    }
};

#endif
