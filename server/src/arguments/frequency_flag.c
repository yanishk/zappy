/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** frequency_flag
*/

#include "server.h"

int frequency_flag(const char **av, int i, bool *is_a_team_name,
    arguments_t *arg)
{
    if (strcmp(av[i], "-f") == 0) {
        *is_a_team_name = false;
        arg->freq = atoi(av[i + 1]);
        if (arg->freq <= 0) {
            fprintf(stderr, INVALID_FREQUENCY);
            return EXIT_WITH_ERROR;
        }
    }
    return EXIT_WITH_SUCCESS;
}
