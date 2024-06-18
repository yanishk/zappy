/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** immortal_flag
*/

#include "server.h"

int immortal_flag(int, const char **av, int *i, arguments_t *arg)
{
    if (strcmp("true", av[*i + 1]) == 0) {
        arg->immortal = true;
    } else if (strcmp("false", av[*i + 1]) == 0) {
        arg->immortal = false;
    } else {
        fprintf(stderr, INVALID_FLAG_ARGUMENT(IMMORTAL));
        return EXIT_WITH_ERROR;
    }
    *i += 1;
    return EXIT_WITH_SUCCESS;
}
