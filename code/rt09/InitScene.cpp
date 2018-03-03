#include "Draw.h"
#include "World.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Parallelogram.h"
#include "L_Parallelogram.h"
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
    world.objects.push_back(new Cap(c + d*(rad-h), rad, -d, ang, mat));
    world.objects.push_back(new Cap(c - d*(rad-h), rad, d, ang, mat));
}

void initScene() {
	// Тут устанавливаются глобальные константы: камера, освещение
	world.cameraPos = Vector3(-15.0, -15.0, 14.0);
	world.forwardDir = normalize(-world.cameraPos);
	world.upwardDir = Vector3(0.0, 0.0, 1.0);
	world.upwardDir -= world.forwardDir * dot(world.forwardDir, world.upwardDir);
	world.cameraAOV = 100.0 / 180.0 * PI;
	world.backgroundColor = Color(0.5, 1.0, 0.7);
	world.globalLightAmbient = Color::WHITE * 0.2;
	world.globalLightDiffuse = Color::WHITE * 0.8;
	world.globalLightDirection = normalize(Vector3(1.0, 2.0, -1.5));

	// Материалы
	static Material matYellow;   matYellow.color = Color::YELLOW;

	static Material matWhite;
    matWhite.color = Color::WHITE * 0.7;

	static Material matGlass;
	matGlass.color = Color::BLACK;
	matGlass.transparencyColor = Color::WHITE * 0.8;
	matGlass.transparencyIndex = 1.3;
	matGlass.mirrorColor = Color::WHITE * 0.05;

	static Material matMirror;
	matMirror.mirrorColor = Color::WHITE * 0.9;

	static Material matMirrorRed;
	matMirrorRed.mirrorColor = Color(1.0, 0.0, 0.0);

	static Material matMirrorGreen;
	matMirrorGreen.mirrorColor = Color(0.0, 1.0, 0.0);

	static Material matMirrorBlue;
	matMirrorBlue.mirrorColor = Color(0.0, 0.0, 1.0);

	// Объекты
    world.objects.push_back(new L_Parallelogram(
        Vector3(-10.0, -10.0, 0.0), Vector3(10.0, -10.0, 0.0), Vector3(10.0, 10.0, 0.0),
        &matWhite, 0.05
    ));

    world.objects.push_back(new Parallelogram(
        Vector3(2.0, 10.0, 0.0), Vector3(6.0, 10.0, 0.0), Vector3(6.0, 10.0, 8.0),
        &matMirrorRed
    ));
    world.objects.push_back(new Parallelogram(
        Vector3(9.0, 7.0, 0.0), Vector3(10.0, 3.0, 0.0), Vector3(10.0, 3.0, 8.0),
        &matMirrorBlue
    ));
    world.objects.push_back(new Parallelogram(
        Vector3(7.0, 10.0, 0.0), Vector3(9.0, 8.0, 0.0), Vector3(9.0, 8.0, 8.0),
        &matMirrorGreen
    ));

    createPrlpd(Vector3(5.0, -5.0, 0.0), Vector3(2.0, 0.0, 0.0), Vector3(0.0, 3.0, 0.0), Vector3(0.0, 0.0, 4.0), &matWhite);
    createLens(Vector3(-4.0, -10.0, 5.0), normalize(Vector3(0.5, 1.0, -4.0)), 2.0, 0.3, &matGlass);
    createPrlpd(Vector3(6.0, -8.0, 0.0), Vector3(2.0, 0.0, 0.0), Vector3(0.0, 2.0, 0.0), Vector3(0.0, 0.0, 7.0), &matYellow);
    createPrlpd(Vector3(-8.0, 3.0, 0.0), Vector3(5.0, 0.0, 0.0), Vector3(0.0, 0.5, 0.0), Vector3(0.0, 0.0, 6.0), &matGlass);
    createPrlpd(Vector3(-9.0, 5.0, 0.0), Vector3(3.0, 0.0, 0.0), Vector3(0.0, 3.0, 0.0), Vector3(0.0, 0.0, 3.0), &matYellow);
}
