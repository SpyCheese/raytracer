#ifndef __COLOR_H__
#define __COLOR_H__
#include "Common.h"
// Color - тип, хранящий цвет в формате rgb. Каждая компонента - от 0.0 до 1.0
// Есть основные операции над цветами и константы

struct Color {
	double r, g, b;

	Color() : r(0.0), g(0.0), b(0.0) {}
	Color(double r, double g, double b) : r(r), g(g), b(b) {}

	Color & operator += (Color const & c) { r += c.r; g += c.g; b += c.b; return *this; }
	Color & operator -= (Color const & c) { r -= c.r; g -= c.g; b -= c.b; return *this; }
	Color & operator *= (Color const & c) { r *= c.r; g *= c.g; b *= c.b; return *this; }
	Color & operator /= (Color const & c) { r /= c.r; g /= c.g; b /= c.b; return *this; }
	Color & operator *= (double c) { r *= c; g *= c; b *= c; return *this; }
	Color & operator /= (double c) { r /= c; g /= c; b /= c; return *this; }

	static const Color RED, GREEN, BLUE, BLACK, WHITE, GREY, YELLOW, MAGENTA, CYAN;
};

inline Color operator + (Color const & c1, Color const & c2) { return Color(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b); }
inline Color operator - (Color const & c1, Color const & c2) { return Color(c1.r-c2.r, c1.g-c2.g, c1.b-c2.b); }
inline Color operator * (Color const & c1, Color const & c2) { return Color(c1.r*c2.r, c1.g*c2.g, c1.b*c2.b); }
inline Color operator / (Color const & c1, Color const & c2) { return Color(c1.r/c2.r, c1.g/c2.g, c1.b/c2.b); }
inline Color operator * (Color const & c1, double c2) { return Color(c1.r*c2, c1.g*c2, c1.b*c2); }
inline Color operator / (Color const & c1, double c2) { return Color(c1.r/c2, c1.g/c2, c1.b/c2); }
inline Color operator * (double c1, Color const & c2) { return Color(c1*c2.r, c1*c2.g, c1*c2.b); }
inline Color operator / (double c1, Color const & c2) { return Color(c1/c2.r, c1/c2.g, c1/c2.b); }
inline bool operator == (Color const & c1, Color const & c2) { return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b; }
inline bool operator != (Color const & c1, Color const & c2) { return c1.r != c2.r || c1.g != c2.g || c1.b != c2.b; }

#endif
