#include "Functions.h"
#include "World.h"

// Возвращает освещённость точки
// Бросает много (RAYS_COUNT) лучей в направлении света с небольшим отклонением, усредняет
Color getLight(Vector3 const & pos, Vector3 const & normal) {
	static const int RAYS_COUNT = 80;
	double globalLightIntensity = 0.0;
	bool wasCross = false;
	for (int i = 0; i < RAYS_COUNT; ++i) {
		Vector3 dir = -world.globalLightDirection;
		if (i > 10 && !wasCross) {
			// Тут применена оптимизация:
			// Если первые 10 лучей не врезались в объект, то считаем, что остальные - тоже
			globalLightIntensity += (RAYS_COUNT - i) * dot(normal, dir);
			break;
		}
		dir.x += (rand() * 0.04 / RAND_MAX - 0.02);
		dir.y += (rand() * 0.04 / RAND_MAX - 0.02);
		dir.z += (rand() * 0.04 / RAND_MAX - 0.02);
		dir = normalize(dir);
		double d = dot(normal, dir);
		if (d > 0.0 && getFirstCross(pos, dir).first == nullptr)
			globalLightIntensity += d;
		else
			wasCross = true;
	}
	globalLightIntensity /= RAYS_COUNT;
	return globalLightIntensity * world.globalLightDiffuse + world.globalLightAmbient;
}
