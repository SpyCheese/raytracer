#include "Material.h"
#include "Functions.h"

// Эта функция вычисляет цвет поверхности по её материалу, положению в пространстве, направлению взгляда и нормали
// Тут вычисляется отражение от зеркала
Color getMaterialColor(Material * mat, Vector3 const & pos, Vector3 const & dir, Vector3 normal) {
	bool inv = false;
	double d = dot(dir, normal);
	if (d > 0.0) {
		normal = -normal;
		inv = true;
		d = -d;
	}
	Color res = Color::BLACK;
	// Цвет самой поверхности
	if (mat->color != Color::BLACK)
		res += mat->color * getLight(pos, normal);
	// Отражённый свет
	if (mat->mirrorColor != Color::BLACK)
		res += traceRay(pos, dir - 2.0*d*normal) * mat->mirrorColor;
	// Блеск
	if (mat->specularColor != Color::BLACK)
		res += mat->specularColor * getLightSpecular(pos, dir - 2.0*d*normal, mat->shininess);
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
	return res;
}
