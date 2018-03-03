#include <ctime>
#include "Draw.h"
#include "World.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Parallelogram.h"
#include "Cylinder.h"
#include "Cap.h"

World world;

// Функция getFirstCross возвращает первое пересечение луча с каким-нибудь объектом
pair < Object *, double > getFirstCross(Vector3 const & pos, Vector3 const & dir) {
	Object * crossObj = nullptr;
	double crossT = INF;
	for (Object * obj : world.objects) {
		double t = obj->getCrossT(pos, dir);
		if (t < crossT) {
			crossObj = obj;
			crossT = t;
		}
	}
	return {crossObj, crossT};
}

// Функция traceRay возвращает цвет, который виден из заданной точки в заданном направлении
Color traceRay(Vector3 pos, Vector3 dir) {
	// Тут глубина рекурсии поддерживается не больше 8
	static int recDepth = 0;
	++recDepth;
	if (recDepth == 8) {
		--recDepth;
		return world.backgroundColor;
	}

	dir = normalize(dir);
	auto c = getFirstCross(pos, dir);
	Object * crossObj = c.first;
	double crossT = c.second;
	// Если пересечение есть, спрашиваем цвет у объекта, иначе возвращаем цвет фона
	Color res;
	if (crossObj != nullptr)
		res = crossObj->getColor(pos + dir*crossT, dir);
	else
		res = world.backgroundColor;
	--recDepth;
	return res;
}

// Функция render принимает размеры требуемой картинки
vector<vector<Color>> render(int imageH, int imageW) {
	auto image = vector<vector<Color>>(imageH, vector<Color>(imageW));

	// Тут происходит вычисление направлений на пиксели. В итоге получается:
	// corner - направление на левый верхний угол
	// dirX - вектор, равный смещению по картинке вниз на один пиксель
	// dirY - вектор, равный смещению по картинке вправо на один пиксель
	Vector3 leftDir = cross(world.upwardDir, world.forwardDir);
	double aov = world.cameraAOV * 0.5;
	double sLeft = tan(aov);
	double sUp = sLeft * imageH / imageW;
	Vector3 corner = world.forwardDir + world.upwardDir*sUp + leftDir*sLeft;
	Vector3 dirX = world.upwardDir * (-sUp * 2.0 / imageH);
	Vector3 dirY = leftDir * (-sLeft * 2.0 / imageW);

	for (int i = 0; i < imageH; ++i)
		for (int j = 0; j < imageW; ++j) {
			Color c = Color::BLACK;
			// На каждый пиксель бросается несколько лучей, их цвета усредняются
			for (int x1 = -1; x1 <= 1; ++x1)
				for (int y1 = -1; y1 <= 1; ++y1)
					c += traceRay(world.cameraPos, corner + dirX*(i+0.5 + 0.33*x1) + dirY*(j+0.5 + 0.33*y1));
			image[i][j] = c / 9;
		}
	return image;
}

int main() {
	initScene();

	auto timeStart = clock();
	vector<vector<Color>> image = render(600, 1000);
	auto timeEnd = clock();
	printf("Rendered in %.3lf s\n", (timeEnd - timeStart) * 1. / CLOCKS_PER_SEC);

	saveImage(image, "mirror.ppm");
}
