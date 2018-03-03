#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include "Color.h"

// Material - струкура, хранящая свойства поверхности

struct Material {
	// Цвет поверхности
	Color color = Color::BLACK;
	// Цвет, на которое умножается отражённый свет. Если ноль - нет отражения
	Color mirrorColor = Color::BLACK;
	// Блеск
	Color specularColor = Color::BLACK;
	double shininess = 0.0;
};

#endif
