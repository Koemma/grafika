#ifndef CIRCLE_H
#define CIRCLE_H

/**
 * Data of a circle object in Descartes coordinate system
 */

typedef enum {
	PIROS = 1,
	ZOLD = 2,
	KEK = 3
  } Color;

typedef struct Circle
{
	double x;
	double y;
	double radius;
	Color color;
} Circle;

/**
 * Set the data of the circle
 */
void set_circle_data(Circle* circle, double x, double y, double radius, Color color);

/**
 * Calculate the area of the circle.
 */
double calc_circle_area(const Circle* circle);

#endif // CIRCLE_H
