#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <math.h>

#define RAD2DEG 57.29578049f

class Point {
public:
	struct compare_points_by_polar_angle {
		Point* ref; // El punto con menor Y

		compare_points_by_polar_angle(Point* _ref) {
			ref = _ref;
		}

		inline bool operator() (const Point* p1, const Point* p2) {
			Point* a = new Point(p1->x - ref->x, p1->y - ref->y);
			Point* b = new Point(p2->x - ref->x, p2->y - ref->y);
			return a->a < b->a;
		}
	};

	struct compare_points_by_x_coordinate {
		inline bool operator() (const Point* p1, const Point* p2) {
			return p1->x < p2->x;
		}
	};

	// x = r cos (alpha)
	// y = r sen (alpha)
	// r = sqrt(x^2+y^2)
	// a = atan(y/2)
	
	Point();
	Point(float _x, float _y);
	~Point();

	std::string to_String();
	float getX();	
	float getY();
	void randomize(float min, float max);

private:
	float x, y, r, a; // r = radio polar, a = ángulo polar

	void cartesianToPolar();
};