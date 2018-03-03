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
#include "L_Cap.h"
#include "Cylinder.h"
#include "Cap.h"
#include "ChessPlane.h"
#include <iostream>

void createPrlpd(Vector3 const & p, Vector3 const & v1, Vector3 const & v2, Vector3 const & v3, Material * mat) {
	world.objects.push_back(new L_Parallelogram(p+v1, p, p+v2, mat, 0.02));
	world.objects.push_back(new L_Parallelogram(p+v2+v3, p+v3, p+v1+v3, mat, 0.02));
	world.objects.push_back(new L_Parallelogram(p+v2, p, p+v3, mat, 0.02));
	world.objects.push_back(new L_Parallelogram(p+v3+v1, p+v1, p+v2+v1, mat, 0.02));
	world.objects.push_back(new L_Parallelogram(p+v3, p, p+v1, mat, 0.02));
	world.objects.push_back(new L_Parallelogram(p+v1+v2, p+v2, p+v3+v2, mat, 0.02));
}

void createLens(Vector3 const& c, Vector3 const& d, double r, double h, Material *mat) {
    double w = sqrt(r*r+h*h);
    double rad = w*w/(2.0*h);
    double ang = asin(r / rad);
    world.objects.push_back(new L_Cap(c + d*(rad-h), rad, -d, ang, mat, 0.02));
    world.objects.push_back(new L_Cap(c - d*(rad-h), rad, d, ang, mat, 0.02));
}

void initScene() {
	// Тут устанавливаются глобальные константы: камера, освещение
	world.cameraPos = Vector3(15.0, -15.0, 7.0);
	world.forwardDir = normalize(Vector3(-1.0, 1.0, -0.2));
	world.upwardDir = Vector3(0.0, 0.0, 1.0);
	world.upwardDir -= world.forwardDir * dot(world.forwardDir, world.upwardDir);

    world.cameraR = 0.035;
    world.cameraF = 1.0;
    world.cameraD = 1.0;
    world.cameraW = 1.0;

	world.backgroundColor = Color(0.1, 0.1, 0.1);
	world.globalLightAmbient = Color(0.3, 0.3, 0.3);
	world.globalLightDiffuse = Color(0.7, 0.7, 0.7);
	world.globalLightDirection = normalize(Vector3(-1.0, 2.0, -0.7));

	// Материалы
	static Material matRed; matRed.color = Color::RED;
	static Material matWhite; matWhite.color = Color::WHITE * 0.6;
	static Material matDarkRed; matDarkRed.color = Color::RED * 0.3;
	static Material matGreen; matGreen.color = Color::GREEN * 0.5;

	static Material matBlue;
    matBlue.color = Color::BLUE * 0.4;
    matBlue.mirrorColor = Color::BLUE * 0.5 + Color::WHITE * 0.1;

	static Material matYellow;
	matYellow.color = Color::YELLOW * 0.4;
	matYellow.mirrorColor = Color::YELLOW * 0.2;

	static Material matMirror;
	matMirror.color = Color::WHITE * 0.1;
	matMirror.mirrorColor = Color::WHITE * 0.8;

	// И дальше куча кода, который создаёт объекты
	world.objects.push_back(new L_Parallelogram(
		Vector3(-10.0, 10.0, -10.0), Vector3(-10.0, 10.0, 22.0), Vector3(30.0, 10.0, 22.0),
		&matGreen, 0.01
	));
	world.objects.push_back(new L_Parallelogram(
		Vector3(-10.0, -10.0, -10.0), Vector3(-10.0, -10.0, 22.0), Vector3(-10.0, 10.0, 22.0),
		&matGreen, 0.01
	));

	world.objects.push_back(new L_Parallelogram(
		Vector3(-7.0, 5.0, 0.0),
		Vector3(7.0, 5.0, 0.0),
		Vector3(7.0, 10.0, 0.0),
		&matRed, 0.01
	));
	world.objects.push_back(new L_Parallelogram(
		Vector3(-7.0, 5.0, 0.0),
		Vector3(7.0, 5.0, 0.0),
		Vector3(7.0, 5.0, -10.0),
		&matRed, 0.01
	));
	world.objects.push_back(new L_Parallelogram(
		Vector3(7.0, 10.0, 0.0),
		Vector3(7.0, 5.0, 0.0),
		Vector3(7.0, 5.0, -10.0),
		&matRed, 0.01
	));
	world.objects.push_back(new L_Cylinder(
		Vector3(-5.0, 7.0, 0.0),
		Vector3(-5.0, 7.0, 2.0),
		0.7,
		&matYellow, 0.02
	));
	world.objects.push_back(new L_Cap(
		Vector3(4.0, 6.7, 4.0),
		4.0,
		Vector3(0.0, 0.0, -1.0),
		PI / 10.0,
		&matWhite, 0.02
	));
	for (int i = 0; i < 12; ++i) {
		double a = 2.0*PI * i / 12.0;
		world.objects.push_back(new L_Sphere(Vector3(4.0 + 0.8*cos(a), 6.7 + 0.8*sin(a), 0.3), 0.2, &matBlue, 0.01));
	}
	for (int i = 0; i < 8; ++i) {
		double a = 2.0*PI * (i+0.3) / 8.0;
		world.objects.push_back(new L_Sphere(Vector3(4.0 + 0.65*cos(a), 6.7 + 0.65*sin(a), 0.5), 0.2, &matBlue, 0.01));
	}
	for (int i = 0; i < 5; ++i) {
		double a = 2.0*PI * (i+0.7) / 5.0;
		world.objects.push_back(new L_Sphere(Vector3(4.0 + 0.4*cos(a), 6.7 + 0.4*sin(a), 0.7), 0.2, &matBlue, 0.01));
	}
	Vector3 p1 = Vector3(-4.0, 10.0, 5.0);
	Vector3 v1 = Vector3(8.0, 0.0, 0.0);
	Vector3 v2 = Vector3(0.0, -2.0, 0.0);
	Vector3 v3 = Vector3(0.0, 0.0, 0.4);
	world.objects.push_back(new L_Parallelogram(p1, p1+v1, p1+v1+v2, &matDarkRed, 0.01));
	world.objects.push_back(new L_Parallelogram(p1, p1+v1, p1+v1+v3, &matDarkRed, 0.01));
	world.objects.push_back(new L_Parallelogram(p1, p1+v2, p1+v2+v3, &matDarkRed, 0.01));
	world.objects.push_back(new L_Parallelogram(p1+v1+v2+v3, p1+v1+v2, p1+v1, &matDarkRed, 0.01));
	world.objects.push_back(new L_Parallelogram(p1+v1+v2+v3, p1+v1+v3, p1+v3, &matDarkRed, 0.01));
	world.objects.push_back(new L_Parallelogram(p1+v1+v2+v3, p1+v2+v3, p1+v2, &matDarkRed, 0.01));
	world.objects.push_back(new L_Cylinder(p1 + 0.2*v1 + 0.9*v2 + 0.2*v3, p1 + 0.2*v1 - 0.1*v2 - 3*v3, 0.1, &matDarkRed, 0.02));
	world.objects.push_back(new L_Cylinder(p1 + 0.8*v1 + 0.9*v2 + 0.2*v3, p1 + 0.8*v1 - 0.1*v2 - 3*v3, 0.1, &matDarkRed, 0.02));

	p1 = Vector3(-10.0, -6.0, 1.0);
	v1 = Vector3(0.0, 12.0, 0.0);
	v2 = Vector3(3.0, 0.0, 0.0);
	v3 = Vector3(0.0, 0.0, 0.3);
	world.objects.push_back(new L_Parallelogram(p1, p1+v1, p1+v1+v2, &matDarkRed, 0.01));
	world.objects.push_back(new L_Parallelogram(p1, p1+v1, p1+v1+v3, &matDarkRed, 0.01));
	world.objects.push_back(new L_Parallelogram(p1, p1+v2, p1+v2+v3, &matDarkRed, 0.01));
	world.objects.push_back(new L_Parallelogram(p1+v1+v2+v3, p1+v1+v2, p1+v1, &matDarkRed, 0.01));
	world.objects.push_back(new L_Parallelogram(p1+v1+v2+v3, p1+v1+v3, p1+v3, &matDarkRed, 0.01));
	world.objects.push_back(new L_Parallelogram(p1+v1+v2+v3, p1+v2+v3, p1+v2, &matDarkRed, 0.01));
	world.objects.push_back(new L_Cylinder(p1 + 0.2*v1 + 0.9*v2 + 0.2*v3, p1 + 0.2*v1 - 0.1*v2 - 3*v3, 0.1, &matDarkRed, 0.01));
	world.objects.push_back(new L_Cylinder(p1 + 0.8*v1 + 0.9*v2 + 0.2*v3, p1 + 0.8*v1 - 0.1*v2 - 3*v3, 0.1, &matDarkRed, 0.01));

	L_Parallelogram * mirror = new L_Parallelogram(
		Vector3(-9.99, -4.0, 2.0),
		Vector3(-9.99, 4.0, 2.0),
		Vector3(-9.99, 4.0, 8.0),
		&matMirror, 0.01
	);
	world.objects.push_back(mirror);
	world.objects.push_back(new L_Cylinder(mirror->p1, mirror->p1+mirror->v1, 0.1, &matBlue, 0.01));
	world.objects.push_back(new L_Cylinder(mirror->p1, mirror->p1+mirror->v2, 0.1, &matBlue, 0.01));
	world.objects.push_back(new L_Cylinder(mirror->p1+mirror->v1+mirror->v2, mirror->p1+mirror->v1, 0.1, &matBlue, 0.01));
	world.objects.push_back(new L_Cylinder(mirror->p1+mirror->v1+mirror->v2, mirror->p1+mirror->v2, 0.1, &matBlue, 0.01));
	world.objects.push_back(new L_Sphere(mirror->p1, 0.1, &matBlue, 0.01));
	world.objects.push_back(new L_Sphere(mirror->p1+mirror->v1, 0.1, &matBlue, 0.01));
	world.objects.push_back(new L_Sphere(mirror->p1+mirror->v2, 0.1, &matBlue, 0.01));
	world.objects.push_back(new L_Sphere(mirror->p1+mirror->v1+mirror->v2, 0.1, &matBlue, 0.01));

	world.objects.push_back(new L_Cylinder(Vector3(-1.0, 8.0, 0.1), Vector3(2.0, 9.0, 0.1), 0.1, &matYellow, 0.01));
	world.objects.push_back(new L_Cylinder(Vector3(-1.2, 9.0, 0.25), Vector3(1.8, 7.0, 0.1), 0.1, &matYellow, 0.01));
}
