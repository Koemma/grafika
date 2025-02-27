#include "brick.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	Brick brick;
	
	set_size(&brick, 5, 5, 8);
    double vol = calc_volume(&brick);
    double surf = calc_surface(&brick);
	
    printf("\nbrick size: %lf, %lf, %lf", brick.a, brick.b, brick.c);
    printf("\nterulet: %lf", vol);
    printf("\nfelszin: %lf", surf);
    if(square(&brick)){
        printf("\nvan negyzet alaku lapja");
    }
    else{
        printf("\nnincs negyzet alaku lapja");
    }
	
	return 0;
}