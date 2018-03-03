#ifndef __COMMON_H__
#define __COMMON_H__

#include <cmath>
#include <cstdlib>
#include <limits>
#include <vector>
using namespace std;
double const PI = acos(-1.0);
double const INF = numeric_limits<double>::infinity();
double const EPS = 1e-6;
inline double sqr(double x) { return x*x; }

#endif
