#include <ctime>
#include "Draw.h"
#include "World.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Parallelogram.h"
#include "Cylinder.h"
#include "Cap.h"
#include <string>
#include <cstdlib>

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
	// Тут глубина рекурсии поддерживается не больше 10
	static int recDepth = 0;
	++recDepth;
	if (recDepth == 10) {
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
        res = Color::WHITE * 8.0 * pow(-dot(dir, world.globalLightDirection), 20.0);
	--recDepth;
	return res;
}

// Функция traceLightRay запускает световой луч, чтобы он сохранился в массивах освещённости объектов
void traceLightRay(Vector3 pos, Vector3 dir, Color const& col) {
	// Тут глубина рекурсии поддерживается не больше 10
	static int recDepth = 0;
	++recDepth;
	if (recDepth == 10) {
		--recDepth;
		return;
	}

	dir = normalize(dir);
	auto c = getFirstCross(pos, dir);
	Object * crossObj = c.first;
	double crossT = c.second;

	if (crossObj != nullptr)
		crossObj->handleLightRay(pos + dir*crossT, dir, col);
	--recDepth;
}

// Функция render принимает размеры требуемой картинки
vector<vector<Color>> render(int imageH, int imageW) {
	auto image = vector<vector<Color>>(imageH, vector<Color>(imageW));

    Vector3 forwardDir = world.forwardDir;
    Vector3 upwardDir = world.upwardDir;
	Vector3 leftDir = cross(upwardDir, forwardDir);
    double cameraH = world.cameraW * imageH / imageW;
	Vector3 corner = forwardDir*(-world.cameraD) - upwardDir * (cameraH / 2.0) - leftDir * (world.cameraW / 2.0);
	Vector3 dirX = upwardDir * (cameraH / imageH);
	Vector3 dirY = leftDir * (world.cameraW / imageW);

	for (int i = 0; i < imageH; ++i)
		for (int j = 0; j < imageW; ++j) {
			Color c = Color::BLACK;
            Vector3 p1 = corner + dirX*i + dirY*j;
            for (int iter = 0; iter < 40; ++iter) {
                double lx = rand() * 2.0 / RAND_MAX - 1.0;
                double ly = rand() * 2.0 / RAND_MAX - 1.0;
                if (lx*lx + ly*ly > 1.0) {
                    --iter;
                    continue;
                }
                lx *= world.cameraR;
                ly *= world.cameraR;
                Vector3 p2 = lx*upwardDir + ly*leftDir;
                Vector3 p11 = p1;
                p11 += dirX * (rand() * 1.0 / RAND_MAX - 0.5);
                p11 += dirY * (rand() * 1.0 / RAND_MAX - 0.5);
                Vector3 p3 = normalize(p2 - p11);
                p3 *= world.cameraF / dot(p3, forwardDir);
                c += traceRay(world.cameraPos + p2, p3 - p2);
            }
			image[i][j] = c / 40;
		}
	return image;
}

void traceLight(Vector3 const &center, double step, int cnt) {
    Vector3 dir = world.globalLightDirection;
    Vector3 v1, v2;
	v1 = Vector3(0.0, 0.0, 1.0);
	v1 -= dir * dot(dir, v1);
    v1 = normalize(v1);
    v2 = cross(v1, dir);
    v1 *= step;
    v2 *= step;
    for (int x = -cnt; x <= cnt; ++x)
        for (int y = -cnt; y <= cnt; ++y)
            traceLightRay(center + dir*(-100.0) + x*v1 + y*v2, dir, world.globalLightDiffuse);
}

int main() {
	initScene();

	auto timeStart = clock();
    traceLight(Vector3(0.0, 10.0, 0.0), LIGHT_STEP, 4000);
	auto time1 = clock();
	printf("Light tracing in %.3lf s\n", (time1 - timeStart) * 1. / CLOCKS_PER_SEC);
    vector<vector<Color>> image = render(600, 1000);
    auto time2 = clock();
    printf("Rendered in %.3lf s\n", (time2 - time1) * 1. / CLOCKS_PER_SEC);
    saveImage(image, "mirror2.ppm");
    printf("Everything: %.3lf s\n", (time2 - timeStart) * 1. / CLOCKS_PER_SEC);
}
