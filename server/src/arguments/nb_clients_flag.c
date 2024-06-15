/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** nb_clients_flag
*/

#include "server.h"

int nb_clients_flag(const char **av, int i, bool *is_a_team_name,
    arguments_t *arg)
{
    if (strcmp(av[i], "-c") == 0) {
        *is_a_team_name = false;
        arg->nb_clients = atoi(av[i + 1]);
        if (arg->nb_clients <= 0) {
            fprintf(stderr, INVALID_NB_CLIENTS);
            return EXIT_WITH_ERROR;
        }
    }
    return EXIT_WITH_SUCCESS;
}
