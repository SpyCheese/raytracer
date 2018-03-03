#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include "Common.h"
#include "Vector3.h"
#include "Object.h"
#include "Color.h"
#include "Material.h"

pair < Object *, double > getFirstCross(Vector3 const & pos, Vector3 const & dir);
Color traceRay(Vector3 pos, Vector3 dir);
Color getMaterialColor(Material * mat, Vector3 const & pos, Vector3 const & dir, Vector3 normal);
Color materialHandleLightRay(Material * mat, Vector3 const & pos, Vector3 const & dir, Vector3 normal, Color const& col);
void traceLightRay(Vector3 pos, Vector3 dir, Color const& col);
void initScene();

#endif
