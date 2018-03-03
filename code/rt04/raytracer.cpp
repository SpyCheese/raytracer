#include "Draw.h"
#include "World.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include <ctime>

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
	dir = normalize(dir);
	auto c = getFirstCross(pos, dir);
	Object * crossObj = c.first;
	double crossT = c.second;
	// Если пересечение есть, спрашиваем цвет у объекта, иначе возвращаем цвет фона
	if (crossObj != nullptr)
		return crossObj->getColor(pos + dir*crossT, dir);
	else
		return world.backgroundColor;
}

// Возвращает освещённость точки
Color getLight(Vector3 const & pos, Vector3 const & normal) {
	if (getFirstCross(pos, -world.globalLightDirection).first == nullptr)
		return world.globalLightDiffuse * max(0.0, dot(normal, -world.globalLightDirection)) + world.globalLightAmbient;
	else
		return world.globalLightAmbient;
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
	world.cameraPos = Vector3(0.0, 0.0, 5.0);
	world.forwardDir = Vector3(1.0, 0.0, 0.0);
	world.upwardDir = Vector3(0.0, 0.0, 1.0);
	world.cameraAOV = 120.0 / 180.0 * PI;
	world.backgroundColor = Color(0.1, 0.1, 0.1);
	world.globalLightAmbient = Color(0.1, 0.1, 0.1);
	world.globalLightDiffuse = Color(0.9, 0.9, 0.9);
	world.globalLightDirection = normalize(Vector3(1.0, 1.0, -1.0));

	world.objects.push_back(new Plane(
		Vector3(0.0, 0.0, 0.0),
		Vector3(0.0, 0.0, 1.0),
		Color::GREEN
	));

	world.objects.push_back(new Sphere(
		Vector3(12.0, 5.0, 3.0),
		4.0,
		Color::RED
	));

	world.objects.push_back(new Sphere(
		Vector3(12.0, 5.0, 7.5),
		0.5,
		Color::MAGENTA
	));

	world.objects.push_back(new Triangle(
		Vector3(5.0, -2.0, 0.0),
		Vector3(11.0, -2.0, 0.0),
		Vector3(5.0, -2.0, 10.0),
		Color::YELLOW
	));

	auto timeStart = clock();
	vector<vector<Color>> image = render(600, 1000);
	auto timeEnd = clock();
	printf("Rendered in %.3lf s\n", (timeEnd - timeStart) * 1. / CLOCKS_PER_SEC);

	saveImage(image, "antialiasing.ppm");
}
