#include "Material.h"
#include "Functions.h"
#include "World.h"

// Тут вычисляется отражение от зеркала, преломление, ещё ambient-освещение
Color getMaterialColor(Material * mat, Vector3 const & pos, Vector3 const & dir, Vector3 normal) {
	bool inv = false;
	double d = dot(dir, normal);
	if (d > 0.0) {
		normal = -normal;
		inv = true;
		d = -d;
	}
	Color res = Color::BLACK;
	// Отражённый свет
	if (mat->mirrorColor != Color::BLACK)
		res += traceRay(pos, dir - 2.0*d*normal) * mat->mirrorColor;
	// Прозрачность
	if (mat->transparencyColor != Color::BLACK) {
		double n = (inv ? 1.0 / mat->transparencyIndex : mat->transparencyIndex);
        double h = sqrt(max(0.0, 1.0 - d*d));
        double w = n*n - h*h;
        if (w >= 0.0) {
            double x = sqrt(w) + d;
            Vector3 dir1 = dir - normal*x;
            res += mat->transparencyColor * traceRay(pos, dir1);
        }
	}
    // Ambient-освещение
    res += world.globalLightAmbient * mat->color;
	return res;
}

Color materialHandleLightRay(Material * mat, Vector3 const & pos, Vector3 const & dir, Vector3 normal, Color const& col) {
	bool inv = false;
	double d = dot(dir, normal);
	if (d > 0.0) {
		normal = -normal;
		inv = true;
		d = -d;
	}
	// Отражённый свет
	if (mat->mirrorColor != Color::BLACK)
		traceLightRay(pos, dir - 2.0*d*normal, col * mat->mirrorColor);
	// Прозрачность
	if (mat->transparencyColor != Color::BLACK) {
		double n = (inv ? 1.0 / mat->transparencyIndex : mat->transparencyIndex);
        double h = sqrt(max(0.0, 1.0 - d*d));
        double w = n*n - h*h;
        if (w >= 0.0) {
            double x = sqrt(w) + d;
            Vector3 dir1 = dir - normal*x;
            traceLightRay(pos, dir1, col * mat->transparencyColor);
        }
	}

	return col * mat->color;
}
