#include "Draw.h"

int main() {
	vector<vector<Color>> a(300, vector<Color>(200, Color::GREY));
	for (int i = 0; i < 100; ++i)
		for (int j = 0; j < 100; ++j)
			a[10 + i][10 + j] = Color(i / 100.0, j / 100.0, 1.0);
	saveImage(a, "draw_example.ppm");
}
