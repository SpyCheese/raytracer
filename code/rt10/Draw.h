#ifndef __DRAW_H__
#define __DRAW_H__
#include <vector>
#include <cstdio>
#include <cstdint>
#include "Color.h"
using namespace std;

// Функция saveImage сохраняет картинку в файл в формате ppm
// Это очень простой формат, о нём можно почитать на Википедии: 
// https://ru.wikipedia.org/wiki/Portable_anymap
//
// image[x][y] - цвет соответствующего пикселя,
// при этом ось OX направлена сверху вниз, OY - слева нараво.

inline void saveImage(vector<vector<Color>> const & image, char const * filename) {
	int w = (int)image.size();
	int h = image.empty() ? 0 : (int)image[0].size();
	FILE * f = fopen(filename, "wb");
	fprintf(f, "P6\n%d %d\n 255\n", h, w);
	for (auto const & r : image)
		for (Color c : r) {
			uint8_t rgb[3]; 
			rgb[0] = (uint8_t)min(255, max(0, (int)(c.r * 255)));
			rgb[1] = (uint8_t)min(255, max(0, (int)(c.g * 255)));
			rgb[2] = (uint8_t)min(255, max(0, (int)(c.b * 255)));
			fwrite(rgb, 3, 1, f);
		}
	fclose(f);
}

#endif
