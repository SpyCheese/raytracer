#ifndef __WORLD_H__
#define __WORLD_H__
#include "Vector3.h"
#include "Color.h"
#include "Object.h"

// World - структура, хранящая всю информацию о сцене

struct World {
	// Позиция камеры и направление. Направления вперёд должны быть нормализованы и перпендикулярны.
	Vector3 cameraPos, forwardDir, upwardDir;
	// Угол обзора (angle of view) - угол между направлениями на крайние слева и справа точки, которые видно
	double cameraAOV;
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
