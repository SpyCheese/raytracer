#ifndef __WORLD_H__
#define __WORLD_H__
#include "Vector3.h"
#include "Color.h"
#include "Object.h"

// World - структура, хранящая всю информацию о сцене

struct World {
	// Параметры камеры
	Vector3 cameraPos, forwardDir, upwardDir;
    double cameraF, cameraD, cameraR, cameraW;
	// Цвет фона
	Color backgroundColor;

	// Глобальное освещение
	Vector3 globalLightDirection;
	Color globalLightDiffuse, globalLightAmbient;

	// Объекты на сцене
	vector < Object* > objects;

	~World() {
		for (Object * obj : objects)
			delete obj;
	}
};
extern World world;

#endif
