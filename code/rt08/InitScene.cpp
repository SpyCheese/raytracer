#include "Draw.h"
#include "World.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Parallelogram.h"
#include "Cylinder.h"
#include "Cap.h"
#include "ChessPlane.h"
#include <iostream>

void createPrlpd(Vector3 const & p, Vector3 const & v1, Vector3 const & v2, Vector3 const & v3, Material * mat) {
	world.objects.push_back(new Parallelogram(p+v1, p, p+v2, mat));
	world.objects.push_back(new Parallelogram(p+v2+v3, p+v3, p+v1+v3, mat));
	world.objects.push_back(new Parallelogram(p+v2, p, p+v3, mat));
	world.objects.push_back(new Parallelogram(p+v3+v1, p+v1, p+v2+v1, mat));
	world.objects.push_back(new Parallelogram(p+v3, p, p+v1, mat));
	world.objects.push_back(new Parallelogram(p+v1+v2, p+v2, p+v3+v2, mat));
}

void createLens(Vector3 const& c, Vector3 const& d, double r, double h, Material *mat) {
    double w = sqrt(r*r+h*h);
    double rad = w*w/(2.0*h);
    double ang = asin(r / rad);
    world.objects.push_back(new Cap(c + d*(rad-h), rad, -d, ang, mat));
    world.objects.push_back(new Cap(c - d*(rad-h), rad, d, ang, mat));
}

void initScene() {
	// Тут устанавливаются глобальные константы: камера, освещение
	world.cameraPos = Vector3(0.0, -6.0, 9.0);
	world.forwardDir = normalize(Vector3(0.5, 1.0, -0.5));
	world.upwardDir = Vector3(0.0, 0.0, 1.0);
	world.upwardDir -= world.forwardDir * dot(world.forwardDir, world.upwardDir);
	world.cameraAOV = 100.0 / 180.0 * PI;
	world.backgroundColor = Color(0.5, 1.0, 0.7);
	world.globalLightAmbient = Color(0.3, 0.3, 0.3);
	world.globalLightDiffuse = Color(0.7, 0.7, 0.7);
	world.globalLightDirection = normalize(Vector3(-1.0, 2.0, -1.5));

	// Материалы
	static Material matWhite; matWhite.color = Color::WHITE;
	static Material matBlack; matBlack.color = Color::WHITE * 0.1;
	static Material matRed;   matRed.color = Color::RED;

	static Material matGreen;
    matGreen.color = Color::GREEN * 0.5;
    matGreen.mirrorColor = Color::GREEN * 0.1;
    matGreen.specularColor = Color::WHITE;
    matGreen.shininess = 5.0;

	static Material matGlass;
	matGlass.color = Color::BLACK;
	matGlass.transparencyColor = Color::WHITE;
	matGlass.transparencyIndex = 1.3;
	matGlass.mirrorColor = Color::WHITE * 0.2;

	static Material matGlass1;
	matGlass1.color = Color::WHITE * 0.1;
	matGlass1.transparencyColor = Color::WHITE;
	matGlass1.transparencyIndex = 1.2;
	matGlass1.shininess = 7.0;
	matGlass1.specularColor = Color::WHITE;

	// Объекты
	world.objects.push_back(new ChessPlane(
		Vector3(0.0, 0.0, 0.0),
		Vector3(0.0, 0.0, 1.0),
		6.1,
		&matWhite,
		&matBlack
	));
	world.objects.push_back(new Sphere(
		Vector3(13.0, 15.0, 3.0), 3.0, &matRed
	));
	world.objects.push_back(new Sphere(
		Vector3(20.0, 8.0, 2.0), 2.0, &matGreen
	));
	createPrlpd(Vector3(11.0, 11.0, 0.0), Vector3(13.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0), Vector3(0.0, 0.0, 8.0), &matGlass);

    createLens(Vector3(0.0, 15.0, 4.0), normalize(Vector3(-0.5, 0.7, 0.0)), 4.0, 0.5, &matGlass1);

    world.objects.push_back(new Cylinder(Vector3(-10.0, 30.0, 3.0), Vector3(10.0, 30.0, 3.0), 0.2, &matRed));
}
