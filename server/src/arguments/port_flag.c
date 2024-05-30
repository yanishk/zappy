/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** port_flag
*/

#include <string.h>
#include <stdlib.h>
#include "server.h"

int port_flag(const char **av, int i, bool *is_a_team_name, arguments_t *arg)
{
    if (strcmp(av[i], "-p") == 0) {
        *is_a_team_name = false;
        arg->port = atoi(av[i + 1]);
        if (arg->port <= 0) {
            fprintf(stderr, INVALID_PORT);
            return EXIT_WITH_ERROR;
        }
    }
    return EXIT_WITH_SUCCESS;
}
