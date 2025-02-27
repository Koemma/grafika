#ifndef BRICK_H
#define BRICK_H
#include <stdbool.h>

typedef struct Brick
{
	double a;
	double b;
	double c;
} Brick;

void set_size(Brick* brick, double a, double b, double c);
double calc_volume(Brick* brick);
double calc_surface(Brick* brick);
bool square(Brick* brick);

#endif
