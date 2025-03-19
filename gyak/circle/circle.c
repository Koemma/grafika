#include "circle.h"
#include <SDL2/SDL.h>

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

void draw_circle_lines(SDL_Renderer* renderer, Circle circle, int steps) {
    double angle_step = 2 * M_PI / steps;
    double angle = 0;
    double x0 = circle.x + circle.radius * cos(angle);
    double y0 = circle.y + circle.radius * sin(angle);
    SDL_SetRenderDrawColor(renderer, circle.color.r, circle.color.g, circle.color.b, 255);
    for (int i = 1; i <= steps; i++) {
        angle += angle_step;
        double x1 = circle.x + circle.radius * cos(angle);
        double y1 = circle.y + circle.radius * sin(angle);
        SDL_RenderDrawLine(renderer, (int)x0, (int)y0, (int)x1, (int)y1);
        x0 = x1;
        y0 = y1;
    }
}

void draw_circle_by_steps(SDL_Renderer* renderer, Circle circle, int step_count) {
    draw_circle_lines(renderer, circle, step_count);
}

void draw_circle_by_angle(SDL_Renderer* renderer, Circle circle, double angle_deg) {
    int steps = (int)(360.0 / angle_deg);
    draw_circle_lines(renderer, circle, steps);
}

void draw_circle_by_max_length(SDL_Renderer* renderer, Circle circle, double max_length) {
    double angle_step = 2 * asin(max_length / (2 * circle.radius));
    int steps = (int)(2 * M_PI / angle_step);
    draw_circle_lines(renderer, circle, steps);
}