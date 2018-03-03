#include "Draw.h"
#include "World.h"
#include "Plane.h"
#include <ctime>

World world;

// Функция traceRay возвращает цвет, который виден из заданной точки в заданном направлении
Color traceRay(Vector3 pos, Vector3 dir) {
	dir = normalize(dir);

	// Ищем ближайшее пересечение
	Object * crossObj = nullptr;
	double crossT = INF;
	for (Object * obj : world.objects) {
		double t = obj->getCrossT(pos, dir);
		if (t < crossT) {
			crossObj = obj;
			crossT = t;
		}
	}

	// Если пересечение есть, спрашиваем цвет у объекта, иначе возвращаем цвет фона
	if (crossObj != nullptr)
		return crossObj->getColor(pos + dir*crossT, dir);
	else
		return world.backgroundColor;
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
		for (int j = 0; j < imageW; ++j)
			image[i][j] = traceRay(world.cameraPos, corner + dirX*(i+0.5) + dirY*(j+0.5));
	return image;
}

int main() {
	world.cameraPos = Vector3(0.0, 0.0, 5.0);
	world.forwardDir = Vector3(1.0, 0.0, 0.0);
	world.upwardDir = Vector3(0.0, 0.0, 1.0);
	world.cameraAOV = 120.0 / 180.0 * PI;
	world.backgroundColor = Color::BLACK;

	world.objects.push_back(new Plane(
		Vector3(0.0, 0.0, 0.0),
		Vector3(0.0, 0.0, 1.0),
		Color::GREEN
	));

	auto timeStart = clock();
	vector<vector<Color>> image = render(400, 600);
	auto timeEnd = clock();
	printf("Rendered in %.3lf s\n", (timeEnd - timeStart) * 1. / CLOCKS_PER_SEC);

	saveImage(image, "plane.ppm");
}
