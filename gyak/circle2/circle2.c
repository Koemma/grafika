#include "circle2.h"
#include <math.h>
#include <stdbool.h>

void set_circle_data(Circle* circle, double x, double y, double radius, Color color) {
    circle->x = x;
    circle->y = y;
    circle->radius = radius;
    circle->color = color;
    circle->is_dragged = false;
}

bool is_point_in_circle(int px, int py, const Circle* circle) {
    double dx = px - circle->x;
    double dy = py - circle->y;
    return dx*dx + dy*dy <= circle->radius * circle->radius;
}

void draw_circle(SDL_Renderer* renderer, const Circle* circle) {
    SDL_SetRenderDrawColor(renderer, circle->color.r, circle->color.g, circle->color.b, 255);

    int steps = 100;
    double angle_step = 2 * M_PI / steps;
    for (int i = 0; i < steps; ++i) {
        double a1 = i * angle_step;
        double a2 = (i + 1) * angle_step;
        int x1 = (int)(circle->x + circle->radius * cos(a1));
        int y1 = (int)(circle->y + circle->radius * sin(a1));
        int x2 = (int)(circle->x + circle->radius * cos(a2));
        int y2 = (int)(circle->y + circle->radius * sin(a2));
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}

void draw_cross(SDL_Renderer* renderer, const Circle* circle) {
    int x = (int)circle->x;
    int y = (int)circle->y;
    int size = (int)(circle->radius / 2);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, x - size, y, x + size, y);
    SDL_RenderDrawLine(renderer, x, y - size, x, y + size);
}
