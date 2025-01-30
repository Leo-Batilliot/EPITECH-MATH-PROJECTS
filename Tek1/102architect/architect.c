/*
** EPITECH PROJECT, 2024
** B-MAT-100-LIL-1-1-102architect-damien.lecoeur
** File description:
** architect
*/
#include "my.h"

static int is_valid_int(const char *str)
{
    if (!str || *str == '\0')
        return 0;
    if (*str == '-' || *str == '+')
        str++;
    while (*str) {
        if (!isdigit(*str))
            exit(84);
        str++;
    }
    return 1;
}

void print_matrix(Matrix_t *matrix)
{
    for (int i = 0; i < 9; ++i)
        if (matrix->m[i / 3][i % 3] < 0.00 && matrix->m[i / 3][i % 3] > -0.005)
            matrix->m[i / 3][i % 3] = 0.00;
    for (int i = 0; i < 9; ++i) {
        printf("%.2f", matrix->m[i / 3][i % 3]);
        if ((i + 1) % 3 == 0)
            printf("\n");
        else
            printf("\t");
    }
}

static int validate_arguments(int argc, char **argv, int i)
{
    if (strcmp(argv[i], "-t") == 0)
        if (i + 2 < argc && is_valid_int(argv[i + 1]) &&
            is_valid_int(argv[i + 2]))
            return 3;
    if (strcmp(argv[i], "-z") == 0)
        if (i + 2 < argc && is_valid_int(argv[i + 1]) &&
            is_valid_int(argv[i + 2]))
            return 3;
    if (strcmp(argv[i], "-r") == 0)
        if (i + 1 < argc && is_valid_int(argv[i + 1]))
            return 2;
    if (strcmp(argv[i], "-s") == 0)
        if (i + 1 < argc && is_valid_int(argv[i + 1]))
            return 2;
    exit(84);
}

void multiply_matrices(Matrix_t *mat2, const Matrix_t *mat1)
{
    Matrix_t result;

    result.m[0][0] = mat1->m[0][0] * mat2->m[0][0] + mat1->m[0][1] *
        mat2->m[1][0] + mat1->m[0][2] * mat2->m[2][0];
    result.m[0][1] = mat1->m[0][0] * mat2->m[0][1] + mat1->m[0][1] *
        mat2->m[1][1] + mat1->m[0][2] * mat2->m[2][1];
    result.m[0][2] = mat1->m[0][0] * mat2->m[0][2] + mat1->m[0][1] *
        mat2->m[1][2] + mat1->m[0][2] * mat2->m[2][2];
    result.m[1][0] = mat1->m[1][0] * mat2->m[0][0] + mat1->m[1][1] *
        mat2->m[1][0] + mat1->m[1][2] * mat2->m[2][0];
    result.m[1][1] = mat1->m[1][0] * mat2->m[0][1] + mat1->m[1][1] *
        mat2->m[1][1] + mat1->m[1][2] * mat2->m[2][1];
    result.m[1][2] = mat1->m[1][0] * mat2->m[0][2] + mat1->m[1][1] *
        mat2->m[1][2] + mat1->m[1][2] * mat2->m[2][2];
    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = 1;
    *mat2 = result;
}

static void apply_transformation(const Matrix_t *transform, double *xy)
{
    double x = xy[0];
    double y = xy[1];
    double hx = x * transform->m[0][0] + y * transform->m[0][1] +
        transform->m[0][2];
    double hy = x * transform->m[1][0] + y * transform->m[1][1] +
        transform->m[1][2];
    double hw = x * transform->m[2][0] + y * transform->m[2][1] +
        transform->m[2][2];

    if (hw < 0.00 && hw > -0.01)
        hw = 0.00;
    if (hy < 0.00 && hy > -0.01)
        hy = 0.00;
    printf("(%.2f, %.2f) => (%.2f, %.2f)\n", x, y, hx, hy);
}

int loop(char **argv, int i, int argc, Matrix_t *transform)
{
    if (strcmp(argv[i], "-t") == 0 && i + 2 < argc) {
        translation_matrix(atoi(argv[i + 1]), atoi(argv[i + 2]), transform);
        return i + 3;
    }
    if (strcmp(argv[i], "-z") == 0 && i + 2 < argc) {
        scaling_matrix(atoi(argv[i + 1]), atoi(argv[i + 2]), transform);
        return i + 3;
    }
    if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) {
        rotation_matrix(atoi(argv[i + 1]), transform);
        return i + 2;
    }
    if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
        reflection_matrix(atoi(argv[i + 1]), transform);
        return i + 2;
    }
    fprintf(stderr, "Invalid transformation: %s\n", argv[i]);
    exit(84);
}

int main(int argc, char **argv)
{
    double xy[2];
    Matrix_t transform = {{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} }};

    for (int i = 3; i < argc; i)
        i += validate_arguments(argc, argv, i);
    if (argc < 4)
        return 84;
    if (!is_valid_int(argv[1]) || !is_valid_int(argv[2]))
        return 84;
    xy[0] = atof(argv[1]);
    xy[1] = atof(argv[2]);
    for (int i = 3; i < argc;)
        i = loop(argv, i, argc, &transform);
    print_matrix(&transform);
    apply_transformation(&transform, xy);
    return 0;
}
