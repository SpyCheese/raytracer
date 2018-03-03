#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include "Color.h"

// Material - струкура, хранящая свойства поверхности

struct Material {
	// Цвет поверхности
	Color color = Color::BLACK;
	// Цвет, на которое умножается отражённый свет. Если ноль - нет отражения
	Color mirrorColor = Color::BLACK;
	// Прозрачность
	Color transparencyColor = Color::BLACK;
	double transparencyIndex = 1.0;
};

#endif
