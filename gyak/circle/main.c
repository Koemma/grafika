#include "circle.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	Circle circle;
	double area;
	Color color = {150, 50, 180};
	
	set_circle_data(&circle, 5, 10, 8, color);
	area = calc_circle_area(&circle);
	
	printf("Circle area: %lf\n", area);
	
	return 0;
}
