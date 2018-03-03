#include "Functions.h"
#include "World.h"

// Возвращает освещённость точки
// Бросает много (RAYS_COUNT) лучей в направлении света с небольшим отклонением, усредняет
Color getLight(Vector3 const & pos, Vector3 const & normal) {
	static const int RAYS_COUNT = 10;
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
		dir.x += (rand() * 0.01 / RAND_MAX - 0.005);
		dir.y += (rand() * 0.01 / RAND_MAX - 0.005);
		dir.z += (rand() * 0.01 / RAND_MAX - 0.005);
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

// Расчитывает отражённый свет для блеска
Color getLightSpecular(Vector3 const & pos, Vector3 const & dir, double shininess) {
	static const int RAYS_COUNT = 10;
	double lightIntensity = 0.0;
	bool wasCross = false;
	for (int i = 0; i < RAYS_COUNT; ++i) {
		Vector3 lightDir = -world.globalLightDirection;
		if (i > 10 && !wasCross) {
			lightIntensity += (RAYS_COUNT - i) * pow(max(0.0, dot(dir, lightDir)), shininess);
			break;
		}
		lightDir.x += (rand() * 0.01 / RAND_MAX - 0.005);
		lightDir.y += (rand() * 0.01 / RAND_MAX - 0.005);
		lightDir.z += (rand() * 0.01 / RAND_MAX - 0.005);
		lightDir = normalize(lightDir);
		if (getFirstCross(pos, lightDir).first == nullptr)
			lightIntensity += pow(max(0.0, dot(dir, lightDir)), shininess);
		else
			wasCross = true;
	}
	lightIntensity /= RAYS_COUNT;
	return lightIntensity * world.globalLightDiffuse;
}
