#include "Draw.h"
#include "World.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Parallelogram.h"
#include "L_Parallelogram.h"
#include "L_ChessParallelogram.h"
#include "L_Sphere.h"
#include "L_Cylinder.h"
#include "Cylinder.h"
#include "Cap.h"
#include "ChessPlane.h"
#include <iostream>

void createPrlpd(Vector3 const & p, Vector3 const & v1, Vector3 const & v2, Vector3 const & v3, Material * mat) {
	world.objects.push_back(new L_Parallelogram(p+v1, p, p+v2, mat, 0.05));
	world.objects.push_back(new L_Parallelogram(p+v2+v3, p+v3, p+v1+v3, mat, 0.05));
	world.objects.push_back(new L_Parallelogram(p+v2, p, p+v3, mat, 0.05));
	world.objects.push_back(new L_Parallelogram(p+v3+v1, p+v1, p+v2+v1, mat, 0.05));
	world.objects.push_back(new L_Parallelogram(p+v3, p, p+v1, mat, 0.05));
	world.objects.push_back(new L_Parallelogram(p+v1+v2, p+v2, p+v3+v2, mat, 0.05));
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
	world.cameraPos = Vector3(-6.0, -12.0, 25.0);
	world.forwardDir = normalize(Vector3(0.5, 1.0, -1.0));
	world.upwardDir = Vector3(0.0, 0.0, 1.0);
	world.upwardDir -= world.forwardDir * dot(world.forwardDir, world.upwardDir);

    world.cameraR = 0.05;
    world.cameraF = 1.0;
    world.cameraD = 1.0;
    world.cameraW = 1.5;

	world.backgroundColor = Color(0.5, 1.0, 0.7);
	world.globalLightAmbient = Color(0.3, 0.3, 0.3);
	world.globalLightDiffuse = Color(0.7, 0.7, 0.7);
	world.globalLightDirection = normalize(Vector3(-1.0, 2.0, -1.5));

	// Материалы
	static Material matWhite; matWhite.color = Color::WHITE;
	static Material matBlack; matBlack.color = Color::WHITE * 0.1;
	static Material matRed;   matRed.color = Color::RED;

	static Material matGreen;
    matGreen.color = Color::GREEN * 0.2;
    matGreen.mirrorColor = Color::GREEN * 0.4 + Color::WHITE * 0.1;

	static Material matGlass;
	matGlass.color = Color::BLACK;
	matGlass.transparencyColor = Color::GREEN;
	matGlass.transparencyIndex = 1.3;
	matGlass.mirrorColor = Color::GREEN * 0.15 + Color::WHITE * 0.05;

	static Material matGlass1;
	matGlass1.color = Color::WHITE * 0.1;
	matGlass1.transparencyColor = Color::WHITE;
	matGlass1.transparencyIndex = 1.3;
	matGlass.mirrorColor = Color::WHITE * 0.2;

	// Объекты
	world.objects.push_back(new L_ChessParallelogram(
		Vector3(-20.0, -20.0, 0.0), Vector3(90.0, -20.0, 0.0), Vector3(90.0, 90.0, 0.0),
		&matWhite, &matBlack, 6.1, 6.1, 0.05
	));
	world.objects.push_back(new L_Sphere(
		Vector3(13.0, 15.0, 3.0), 3.0, &matWhite, 0.05
	));
	world.objects.push_back(new L_Sphere(
		Vector3(20.0, 8.0, 2.0), 2.0, &matGreen, 0.05
	));
	createPrlpd(Vector3(11.0, 11.0, 0.0), Vector3(13.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0), Vector3(0.0, 0.0, 8.0), &matGlass);

    createLens(Vector3(0.0, 15.0, 4.0), normalize(Vector3(-0.5, 1.5, 0.0)), 4.0, 0.5, &matGlass1);

    world.objects.push_back(new L_Cylinder(Vector3(-10.0, 17.0, 3.0), Vector3(10.0, 17.0, 3.0), 0.2, &matRed, 0.1));
}
