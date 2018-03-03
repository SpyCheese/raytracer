#include "Material.h"
#include "Functions.h"

// Эта функция вычисляет цвет поверхности по её материалу, положению в пространстве, направлению взгляда и нормали
// Тут вычисляется отражение от зеркала
Color getMaterialColor(Material * mat, Vector3 const & pos, Vector3 const & dir, Vector3 normal) {
	if (dot(dir, normal) > 1.0)
		normal = -normal;
	Color res = Color::BLACK;
	// Первая компонента цвета - цвет самой поверхности
	if (mat->color != Color::BLACK)
		res += mat->color * getLight(pos, normal);
	// Вторая компонента цвета - отражённый свет
	if (mat->mirrorColor != Color::BLACK)
		res += traceRay(pos, dir - 2.0*dot(dir, normal)*normal) * mat->mirrorColor;
	// Третья - блеск
	if (mat->specularColor != Color::BLACK)
		res += mat->specularColor * getLightSpecular(pos, dir - 2.0*dot(dir, normal)*normal, mat->shininess);
	return res;
}
