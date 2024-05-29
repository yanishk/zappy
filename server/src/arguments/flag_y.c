/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** flag_y
*/

#include <string.h>
#include <stdlib.h>
#include "server.h"

int flag_y(const char **av, int i, bool *is_a_team_name, arguments_t *arg)
{
    if (strcmp(av[i], "-y") == 0) {
        *is_a_team_name = false;
        arg->height = atoi(av[i + 1]);
        if (arg->height <= 0) {
            fprintf(stderr, INVALID_HEIGHT);
            return EXIT_WITH_ERROR;
        }
    }
    return EXIT_WITH_SUCCESS;
}
