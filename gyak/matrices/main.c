#include "matrix.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	float b[3][3];
	float c[3][3];

    init_zero_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;

    printf("\na: \n");
    print_matrix(a);
    printf("\nb: \n");
    print_matrix(b);
    
    add_matrices(a, b, c);
    printf("\nc: \n");
    print_matrix(c);

    //egyseg matrix
    float egyseg_m[3][3];
    init_identity_matrix(egyseg_m);
    printf("\nd: \n");
    print_matrix(egyseg_m);

    //skalaris szorzas
    printf("\nskalaris szorzat: %lf", scalar(a,b));

    //matrix szorzas
    float mult_m[3][3];
    multiply_matrices(a,b,mult_m);
    printf("\nmult_m: \n");
    print_matrix(mult_m);

    //matrix transzformacio
    float pont[3] = {3, -5, 1};
    float pont2[3];
    transform_point(mult_m, pont, pont2);
    printf("\neltolt pont: \n");
    for (size_t i = 0; i < 3; i++)
    {
        printf(" %.2f, ", pont2[i]);
    }

    //matrix forgatas
    float rot_m[3][3];
    multiply_matrices(a,b,rot_m);
    rotate(rot_m, 30);
    printf("\nrot_m:\n");
    print_matrix(rot_m);

    //matrix skalazas
    float scale_m[3][3];
    multiply_matrices(a,b,scale_m);
    scale(scale_m, 5, 4);
    printf("\nscale_m:\n");
    print_matrix(scale_m);

    //matrix eltolas
    float shift_m[3][3];
    multiply_matrices(a,b,shift_m);
    shift(shift_m, 5, 4);
    printf("\nshift_m:\n");
    print_matrix(shift_m);

	return 0;
}

