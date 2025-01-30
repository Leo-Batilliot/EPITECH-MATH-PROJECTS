/*
** EPITECH PROJECT, 2024
** B-MAT-100-LIL-1-1-102architect-damien.lecoeur
** File description:
** matrix_calculations
*/
#include "my.h"

void translation_matrix(int tx, int ty, Matrix_t *res)
{
    Matrix_t mat = {{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} }};

    mat.m[0][2] = tx;
    mat.m[1][2] = ty;
    multiply_matrices(res, &mat);
    printf("Translation along vector (%d, %d)\n", tx, ty);
}

void scaling_matrix(int sx, int sy, Matrix_t *res)
{
    Matrix_t mat = {{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} }};

    mat.m[0][0] = sx;
    mat.m[1][1] = sy;
    multiply_matrices(res, &mat);
    printf("Scaling by factors %d and %d\n", sx, sy);
}

void rotation_matrix(int angle_degrees, Matrix_t *mat)
{
    double angle_radians = angle_degrees * (3.14159265358979323846 / 180.0);
    Matrix_t rotation = {{
        {cos(angle_radians), - sin(angle_radians), 0},
        {sin(angle_radians), cos(angle_radians), 0},
        {0, 0, 1}}};

    multiply_matrices(mat, &rotation);
    printf("Rotation by a %d degree angle\n", angle_degrees);
}

void reflection_matrix(int a, Matrix_t *res)
{
    Matrix_t mat = {{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} }};
    double rad = a * 3.14159265358979323846 / 180.0;
    double cos2 = cos(2 * rad);
    double sin2 = sin(2 * rad);

    mat.m[0][0] = cos2;
    mat.m[0][1] = sin2;
    mat.m[1][0] = sin2;
    mat.m[1][1] = -cos2;
    multiply_matrices(res, &mat);
    printf("Reflection over an axis with an inclination angle of %d degrees\n",
        a);
}
