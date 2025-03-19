#include "circle.h"

#include <math.h>
#define M_PI 3.14159265358979323846

void set_circle_data(Circle* circle, double x, double y, double radius, Color color)
{
	circle->x = x;
	circle->y = y;
	if (radius > 0.0) {
		circle->radius = radius;
	} else {
		circle->radius = NAN;
	}
	circle->color = color;

}

double calc_circle_area(const Circle* circle)
{
	double area = circle->radius * circle->radius * M_PI;
	return area;
}
