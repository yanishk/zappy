/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** height_flag
*/

#include "server.h"

int height_flag(int, const char **av, int *i, arguments_t *arg)
{
    if (!is_positive_number(av[*i + 1])) {
        fprintf(stderr, INVALID_FLAG_ARGUMENT(HEIGHT));
        return EXIT_WITH_ERROR;
    }
    arg->height = atoi(av[*i + 1]);
    if (arg->height == 0) {
        fprintf(stderr, INVALID_FLAG_ARGUMENT(HEIGHT));
        return EXIT_WITH_ERROR;
    }
    *i += 1;
    return EXIT_WITH_SUCCESS;
}
