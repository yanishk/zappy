/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** width_flag
*/

#include "server.h"

int width_flag(int, const char **av, int *i, arguments_t *arg)
{
    if (!is_positive_number(av[*i + 1])) {
        fprintf(stderr, INVALID_FLAG_ARGUMENT(WIDTH));
        return EXIT_WITH_ERROR;
    }
    arg->width = atoi(av[*i + 1]);
    if (arg->width == 0) {
        fprintf(stderr, INVALID_FLAG_ARGUMENT(WIDTH));
        return EXIT_WITH_ERROR;
    }
    *i += 1;
    return EXIT_WITH_SUCCESS;
}
