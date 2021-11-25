#include "Point.h"

// Complejidad O(1)
Point::Point() {
	x = 0;
	y = 0;
	r = 0;
	a = 0;
}

// Complejidad O(√(n))
Point::Point(float _x, float _y) {
	x = _x;
	y = _y;
	cartesianToPolar(); // Complejidad O(√(n))
}

// Complejidad O(1)
Point::~Point() { }

// Liga del to_string: https://stackoverflow.com/questions/68398136/to-string-c-time-complexity
// Complejidad O(1)
std::string Point::to_String() {
	std::string tmp = "(" + std::to_string(x) + ", " + std::to_string(y) + ") = (" + std::to_string(r) + ", " + std::to_string(a*RAD2DEG) + ")";
	return tmp;
}

// Complejidad O(1)
float Point::getX() { return x; }

// Complejidad O(1)
float Point::getY() { return y; }

// Liga del rand: http://www.cplusplus.com/forum/general/192823/
// Complejidad O(√(n))
void Point::randomize(float min, float max) {
	x = min + (max - min) * (float)rand() / RAND_MAX;
	y = min + (max - min) * (float)rand() / RAND_MAX;
	cartesianToPolar(); // Complejidad O(√(n))
}

// Liga del sqrt: https://www.geeksforgeeks.org/square-root-of-an-integer/
// Complejidad O(√(n))
void Point::cartesianToPolar() {
	if (x != 0) {
		r = sqrtf(pow(x, 2) + pow(y, 2));
		a = atan2f(y, x);
	} else {
		r = 0;
		a = 0;	
	}
}
