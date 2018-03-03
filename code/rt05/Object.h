#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "Color.h"
#include "Vector3.h"

// Object - базовый класс для объектов.
// Содержит виртуальные функции:
// getCrossT - находит пересечение луча с объектом
//			   Возрвращает такое наименьшее t > 0, что pos + dir*t - это точка пересечения с объектом
//			   Если не пересекается, возвращает INF
// getColor - возвращает цвет объекта. Принимает точку пересениения луча с объектом и его направление

struct Object {
	virtual double getCrossT(Vector3 const & pos, Vector3 const & dir) = 0;
	virtual Color getColor(Vector3 const & pos, Vector3 const & dir) = 0;
	virtual ~Object() {}
};

#endif
