/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** nb_clients_flag
*/

#include "server.h"

int nb_clients_flag(int, const char **av, int *i, arguments_t *arg)
{
    if (!is_positive_number(av[*i + 1])) {
        fprintf(stderr, ARG_MUST_BE_A_NUMBER(NB_CLIENTS));
        return EXIT_WITH_ERROR;
    }
    arg->nb_clients = atoi(av[*i + 1]);
    if (arg->nb_clients == 0) {
        fprintf(stderr, ARG_MUST_BE_A_NUMBER(NB_CLIENTS));
        return EXIT_WITH_ERROR;
    }
    *i += 1;
    return EXIT_WITH_SUCCESS;
}
