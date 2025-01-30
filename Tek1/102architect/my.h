/*
** EPITECH PROJECT, 2024
** myh
** File description:
** task 02
*/
#ifndef TEST_H
    #define TEST_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <string.h>
    #include <ctype.h>

typedef struct {
    double m[3][3];
} Matrix_t;

void multiply_matrices(Matrix_t *mat2, const Matrix_t *mat1);
void reflection_matrix(int a, Matrix_t *res);
void rotation_matrix(int angle_degrees, Matrix_t *mat);
void scaling_matrix(int sx, int sy, Matrix_t *res);
void translation_matrix(int tx, int ty, Matrix_t *res);
int main(int, char **);

#endif /* TEST_H */
