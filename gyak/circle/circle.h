#include <SDL2/SDL.h>
#ifndef CIRCLE_H
#define CIRCLE_H

/**
 * Data of a circle object in Descartes coordinate system
 */

 typedef struct
 {
   unsigned char r;
   unsigned char g;
   unsigned char b;
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

void draw_circle_by_steps(SDL_Renderer* renderer, Circle circle, int step_count);
void draw_circle_by_angle(SDL_Renderer* renderer, Circle circle, double angle_deg);
void draw_circle_by_max_length(SDL_Renderer* renderer, Circle circle, double max_length);

#endif // CIRCLE_H
