#include "brick.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void set_size(Brick* brick, double a, double b, double c)
{
    if (a <= 0 || b <= 0 || c <= 0) {
        printf("hibas adat\n");
        return;
    }

	brick->a = a;
	brick->b = b;
    brick->c = c;
}

double calc_volume(Brick* brick){
    double vol = brick->a * brick->b * brick->c;
    
    return vol;
}

double calc_surface(Brick* brick){
    double surf = 2 * (brick->a * brick->b + brick->a * brick->c + brick->c * brick->b);
    
    return surf;
}

bool square(Brick* brick){
    if (brick->a == brick->b || brick->a == brick->c || brick->c == brick->b) {
        return true;
    }

    return false;
}