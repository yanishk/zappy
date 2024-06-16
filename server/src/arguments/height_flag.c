/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** height_flag
*/

#include "server.h"

int height_flag(const char **av, int *i, bool *is_a_team_name,
    arguments_t *arg)
{
    *is_a_team_name = false;
    if (!is_positive_number(av[*i + 1])) {
        fprintf(stderr, INVALID_HEIGHT);
        return EXIT_WITH_ERROR;
    }
    arg->height = atoi(av[*i + 1]);
    *i += 1;
    return EXIT_WITH_SUCCESS;
}
