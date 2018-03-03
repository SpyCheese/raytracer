#include "Draw.h"
#include "World.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Parallelogram.h"
#include "Cylinder.h"
#include "Cap.h"

void initScene() {
	// Тут устанавливаются глобальные константы: камера, освещение
	world.cameraPos = Vector3(15.0, -15.0, 7.0);
	world.forwardDir = normalize(Vector3(-1.0, 1.0, -0.2));
	world.upwardDir = Vector3(0.0, 0.0, 1.0);
	world.upwardDir -= world.forwardDir * dot(world.forwardDir, world.upwardDir);
	world.cameraAOV = 60.0 / 180.0 * PI;
	world.backgroundColor = Color(0.1, 0.1, 0.1);
	world.globalLightAmbient = Color(0.3, 0.3, 0.3);
	world.globalLightDiffuse = Color(0.7, 0.7, 0.7);
	world.globalLightDirection = normalize(Vector3(-1.0, 2.0, -1.5));

	// Материалы. Сначала сплошные цвета
	static Material matRed; matRed.color = Color::RED;
	static Material matDarkRed; matDarkRed.color = Color::RED * 0.5;
	static Material matGreen; matGreen.color = Color::GREEN * 0.5;

	// Блестящий материал
	static Material matBlue;
	matBlue.color = Color::BLUE * 0.5;
	matBlue.mirrorColor = Color::BLUE * 0.2;
	matBlue.specularColor = Color::WHITE;
	matBlue.shininess = 6.0;

	// Два зеркальных материала
	static Material matYellow;
	matYellow.color = Color::YELLOW * 0.7;
	matYellow.mirrorColor = Color::YELLOW * 0.3;

	static Material matMirror;
	matMirror.color = Color::WHITE * 0.1;
	matMirror.mirrorColor = Color::WHITE * 0.8;

	// И дальше куча кода, который создаёт объекты
	world.objects.push_back(new Plane(
		Vector3(0.0, 10.0, 0.0),
		Vector3(0.0, -1.0, 0.0),
		&matGreen
	));
	world.objects.push_back(new Plane(
		Vector3(-10.0, 0.0, 0.0),
		Vector3(1.0, 0.0, 0.0),
		&matGreen
	));

	world.objects.push_back(new Parallelogram(
		Vector3(-7.0, 5.0, 0.0),
		Vector3(7.0, 5.0, 0.0),
		Vector3(7.0, 10.0, 0.0),
		&matRed
	));
	world.objects.push_back(new Parallelogram(
		Vector3(-7.0, 5.0, 0.0),
		Vector3(7.0, 5.0, 0.0),
		Vector3(7.0, 5.0, -10.0),
		&matRed
	));
	world.objects.push_back(new Parallelogram(
		Vector3(7.0, 10.0, 0.0),
		Vector3(7.0, 5.0, 0.0),
		Vector3(7.0, 5.0, -10.0),
		&matRed
	));
	world.objects.push_back(new Cylinder(
		Vector3(-5.0, 7.0, 0.0),
		Vector3(-5.0, 7.0, 2.0),
		0.7,
		&matYellow
	));
	world.objects.push_back(new Cap(
		Vector3(4.0, 6.7, 4.0),
		4.0,
		Vector3(0.0, 0.0, -1.0),
		PI / 10.0,
		&matYellow
	));
	for (int i = 0; i < 12; ++i) {
		double a = 2.0*PI * i / 12.0;
		world.objects.push_back(new Sphere(Vector3(4.0 + 0.8*cos(a), 6.7 + 0.8*sin(a), 0.3), 0.2, &matBlue));
	}
	for (int i = 0; i < 8; ++i) {
		double a = 2.0*PI * (i+0.3) / 8.0;
		world.objects.push_back(new Sphere(Vector3(4.0 + 0.65*cos(a), 6.7 + 0.65*sin(a), 0.5), 0.2, &matBlue));
	}
	for (int i = 0; i < 5; ++i) {
		double a = 2.0*PI * (i+0.7) / 5.0;
		world.objects.push_back(new Sphere(Vector3(4.0 + 0.4*cos(a), 6.7 + 0.4*sin(a), 0.7), 0.2, &matBlue));
	}
	Vector3 p1 = Vector3(-4.0, 10.0, 5.0);
	Vector3 v1 = Vector3(8.0, 0.0, 0.0);
	Vector3 v2 = Vector3(0.0, -2.0, 0.0);
	Vector3 v3 = Vector3(0.0, 0.0, 0.4);
	world.objects.push_back(new Parallelogram(p1, p1+v1, p1+v1+v2, &matDarkRed));
	world.objects.push_back(new Parallelogram(p1, p1+v1, p1+v1+v3, &matDarkRed));
	world.objects.push_back(new Parallelogram(p1, p1+v2, p1+v2+v3, &matDarkRed));
	world.objects.push_back(new Parallelogram(p1+v1+v2+v3, p1+v1+v2, p1+v1, &matDarkRed));
	world.objects.push_back(new Parallelogram(p1+v1+v2+v3, p1+v1+v3, p1+v3, &matDarkRed));
	world.objects.push_back(new Parallelogram(p1+v1+v2+v3, p1+v2+v3, p1+v2, &matDarkRed));
	world.objects.push_back(new Cylinder(p1 + 0.2*v1 + 0.9*v2 + 0.2*v3, p1 + 0.2*v1 - 0.1*v2 - 3*v3, 0.1, &matDarkRed));
	world.objects.push_back(new Cylinder(p1 + 0.8*v1 + 0.9*v2 + 0.2*v3, p1 + 0.8*v1 - 0.1*v2 - 3*v3, 0.1, &matDarkRed));

	p1 = Vector3(-10.0, -6.0, 1.0);
	v1 = Vector3(0.0, 12.0, 0.0);
	v2 = Vector3(3.0, 0.0, 0.0);
	v3 = Vector3(0.0, 0.0, 0.3);
	world.objects.push_back(new Parallelogram(p1, p1+v1, p1+v1+v2, &matDarkRed));
	world.objects.push_back(new Parallelogram(p1, p1+v1, p1+v1+v3, &matDarkRed));
	world.objects.push_back(new Parallelogram(p1, p1+v2, p1+v2+v3, &matDarkRed));
	world.objects.push_back(new Parallelogram(p1+v1+v2+v3, p1+v1+v2, p1+v1, &matDarkRed));
	world.objects.push_back(new Parallelogram(p1+v1+v2+v3, p1+v1+v3, p1+v3, &matDarkRed));
	world.objects.push_back(new Parallelogram(p1+v1+v2+v3, p1+v2+v3, p1+v2, &matDarkRed));
	world.objects.push_back(new Cylinder(p1 + 0.2*v1 + 0.9*v2 + 0.2*v3, p1 + 0.2*v1 - 0.1*v2 - 3*v3, 0.1, &matDarkRed));
	world.objects.push_back(new Cylinder(p1 + 0.8*v1 + 0.9*v2 + 0.2*v3, p1 + 0.8*v1 - 0.1*v2 - 3*v3, 0.1, &matDarkRed));

	Parallelogram * mirror = new Parallelogram(
		Vector3(-9.99, -4.0, 2.0),
		Vector3(-9.99, 4.0, 2.0),
		Vector3(-9.99, 4.0, 8.0),
		&matMirror
	);
	world.objects.push_back(mirror);
	world.objects.push_back(new Cylinder(mirror->p1, mirror->p1+mirror->v1, 0.1, &matBlue));
	world.objects.push_back(new Cylinder(mirror->p1, mirror->p1+mirror->v2, 0.1, &matBlue));
	world.objects.push_back(new Cylinder(mirror->p1+mirror->v1+mirror->v2, mirror->p1+mirror->v1, 0.1, &matBlue));
	world.objects.push_back(new Cylinder(mirror->p1+mirror->v1+mirror->v2, mirror->p1+mirror->v2, 0.1, &matBlue));
	world.objects.push_back(new Sphere(mirror->p1, 0.1, &matBlue));
	world.objects.push_back(new Sphere(mirror->p1+mirror->v1, 0.1, &matBlue));
	world.objects.push_back(new Sphere(mirror->p1+mirror->v2, 0.1, &matBlue));
	world.objects.push_back(new Sphere(mirror->p1+mirror->v1+mirror->v2, 0.1, &matBlue));

	world.objects.push_back(new Cylinder(Vector3(-1.0, 8.0, 0.1), Vector3(2.0, 9.0, 0.1), 0.1, &matYellow));
	world.objects.push_back(new Cylinder(Vector3(-1.2, 9.0, 0.25), Vector3(1.8, 7.0, 0.1), 0.1, &matYellow));

}
