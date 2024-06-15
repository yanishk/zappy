/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** width_flag
*/

#include "server.h"

int width_flag(const char **av, int i, bool *is_a_team_name, arguments_t *arg)
{
    if (strcmp(av[i], "-x") == 0) {
        *is_a_team_name = false;
        arg->width = atoi(av[i + 1]);
        if (arg->width <= 0) {
            fprintf(stderr, INVALID_WIDTH);
            return EXIT_WITH_ERROR;
        }
    }
    return EXIT_WITH_SUCCESS;
}
