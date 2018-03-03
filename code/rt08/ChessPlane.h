#ifndef __CHESS_PLANE_H__
#define __CHESS_PLANE_H__
#include "Object.h"
#include "Functions.h"

// ChessPlane - бесконечная плоскость с двумя материалами

struct ChessPlane : Object {
	Vector3 point, normal;
	double ss;
	Material * mat1, * mat2;

	ChessPlane(Vector3 const & p, Vector3 const & n, double ss, Material * m1, Material * m2) :
		point(p), normal(normalize(n)), ss(ss), mat1(m1), mat2(m2) {}

	double getCrossT(Vector3 const & pos, Vector3 const & dir) {
		// pos + dir*t лежит в плоскости
		// dot(pos + dir*t - point, normal) == 0
		// dot(pos - point, normal) = -dot(dir, normal)*t
		double t = -dot(pos - point, normal) / dot(dir, normal);
		return t > EPS ? t : INF;
	}

	virtual Color getColor(Vector3 const & pos, Vector3 const & dir) {
		Material * m;
		if ((int(floor(pos.x/ss)) + int(floor(pos.y/ss))) % 2 == 0)
			m = mat1;
		else
			m = mat2;
		return getMaterialColor(m, pos, dir, normal);
	}
};

#endif
