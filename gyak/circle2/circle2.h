#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_CIRCLE_COUNT 5

typedef struct {
    unsigned char r, g, b;
} Color;

typedef struct {
    double x, y;
    double radius;
    Color color;
    bool is_dragged;
} Circle;

void set_circle_data(Circle* circle, double x, double y, double radius, Color color);
bool is_point_in_circle(int px, int py, const Circle* circle);
void draw_circle(SDL_Renderer* renderer, const Circle* circle);
void draw_cross(SDL_Renderer* renderer, const Circle* circle);

#endif
