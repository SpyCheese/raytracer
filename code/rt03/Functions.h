#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include "Common.h"
#include "Vector3.h"
#include "Object.h"
#include "Color.h"

pair < Object *, double > getFirstCross(Vector3 const & pos, Vector3 const & dir);
Color traceRay(Vector3 pos, Vector3 dir);
Color getLight(Vector3 const & pos, Vector3 const & normal);

// Эта функция переворацивает нормаль, если взгляд направлен на обратную поверхность
inline Vector3 getGoodNormal(Vector3 const & normal, Vector3 const & dir) {
	if (dot(normal, dir) > 0.0)
		return -normal;
	return normal;
}

#endif
