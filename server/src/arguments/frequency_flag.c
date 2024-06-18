/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** frequency_flag
*/

#include "server.h"

int frequency_flag(int, const char **av, int *i, arguments_t *arg)
{
    if (!is_positive_number(av[*i + 1])) {
        fprintf(stderr, ARG_MUST_BE_A_NUMBER(FREQUENCY));
        return EXIT_WITH_ERROR;
    }
    arg->freq = atoi(av[*i + 1]);
    if (arg->freq == 0) {
        fprintf(stderr, ARG_MUST_BE_A_NUMBER(FREQUENCY));
        return EXIT_WITH_ERROR;
    }
    *i += 1;
    return EXIT_WITH_SUCCESS;
}
