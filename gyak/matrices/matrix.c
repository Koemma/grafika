#include "matrix.h"

#include <stdio.h>
#include <math.h>


#define PI 3.14159265358979323846

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void init_identity_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            if (i == j)
            {
                matrix[i][j] = 1.0;
            }
            else
            {
                matrix[i][j] = 0.0;
            }
        }
    }
}

float scalar(float matrix1[3][3], float matrix2[3][3])
{
    int i;
    int j;
    float ossz = 0;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            ossz += matrix1[i][j] * matrix2[i][j];
        }
    }

    return ossz;
}

void multiply_matrices(float matrix1[3][3], float matrix2[3][3], float matrix3[3][3])
{
    init_zero_matrix(matrix3);
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            for (size_t k = 0; k < 3; k++)
            {
                matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void transform_point(float matrix[3][3], float pont[3], float pont2[3])
{
    for (size_t i = 0; i < 3; i++)
    {
        pont2[i] = 0;
        for (size_t j = 0; j < 3; j++)
        {
            pont2[i] += matrix[i][j] * pont[j];
        }
    }
}

void rotate(float matrix1[3][3], float szog){
    float rad = szog * PI / 180.0;
    float matrix2[3][3] = {{cos(rad),-sin(rad),0},{sin(rad), cos(rad),0},{0,0,1}};
    float matrix3[3][3];
    multiply_matrices(matrix1, matrix2, matrix3);
}