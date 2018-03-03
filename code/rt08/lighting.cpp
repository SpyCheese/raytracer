#include "Functions.h"
#include "World.h"

// Возвращает освещённость точки
// Бросает много (RAYS_COUNT) лучей в направлении света с небольшим отклонением, усредняет
Color getLight(Vector3 const & pos, Vector3 const & normal) {
	double globalLightIntensity = 0.0;
    Vector3 dir = -world.globalLightDirection;
    double d = dot(normal, dir);
    if (d > 0.0)
        globalLightIntensity = d;
	return globalLightIntensity * world.globalLightDiffuse + world.globalLightAmbient;
}

// Расчитывает отражённый свет для блеска
Color getLightSpecular(Vector3 const & pos, Vector3 const & dir, double shininess) {
	double lightIntensity = 0.0;
    Vector3 lightDir = -world.globalLightDirection;
    lightIntensity += pow(max(0.0, dot(dir, lightDir)), shininess);
	return lightIntensity * world.globalLightDiffuse;
}
