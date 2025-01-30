/*
** EPITECH PROJECT, 2024
** B-MAT-100-LIL-1-1-101pong-leo.batilliot
** File description:
** pong
*/
#include "my.h"

int print_result(struct coordinates *position,
    struct coordinates *vector, struct coordinates *position2, int number)
{
    float res = 0;

    if (vector->z == 0 ||
        position->z + vector->z < 0 && position2->z < 0 ||
        position->z + vector->z > 0 && position2->z > 0) {
        printf("The ball won't reach the paddle.\n");
        return 0;
    }
    res = sqrt(vector->x * vector->x + vector->y * vector->y
        + vector->z * vector->z);
    res = asin(fabs(vector->z) / res) * (180.0 / 3.14159265358979323846264338);
    if (res < 0.005)
        printf("The ball won't reach the paddle.\n");
    else
        printf("The incidence angle is:\n%.2f degrees\n", res);
    return 0;
}

int pong(int ac, char **av)
{
    coordinates_t position = {atof(av[1]), atof(av[2]), atof(av[3])};
    coordinates_t vector = {atof(av[4]) - position.x,
        atof(av[5]) - position.y, atof(av[6]) - position.z};
    int number = atoi(av[7]);
    coordinates_t position2 = {position.x + vector.x * (number + 1),
        position.y + vector.y * (number + 1),
        position.z + vector.z * (number + 1)};

    printf("The velocity vector of the ball is:\n(%.2f, %.2f, %.2f)\n",
        vector.x, vector.y, vector.z);
    printf("At time t + %i, ball coordinates will be:\n(%.2f, %.2f, %.2f)\n",
        number, position2.x, position2.y, position2.z);
    print_result(&position, &vector, &position2, number);
    return 0;
}

int is_integer(const char *str)
{
    char *endptr;

    strtol(str, &endptr, 10);
    return *endptr == '\0';
}

int is_float(const char *str)
{
    char *endptr;

    strtod(str, &endptr);
    return *endptr == '\0';
}

int main(int ac, char **av)
{
    if (ac != 8)
        return 84;
    for (int i = 1; i < ac - 1; i++)
        if (!is_integer(av[i]) && !is_float(av[i]))
            return 84;
    if (!is_integer(av[ac - 1]))
        return 84;
    if (atoi(av[7]) < 1)
        return 84;
    return pong(ac, av);
}
