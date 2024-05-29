/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** flag_n
*/

#include <string.h>
#include <stdlib.h>
#include "server.h"

int flag_n(const char **av, int i, bool *is_a_team_name, arguments_t *)
{
    if (strcmp(av[i], "-n") == 0) {
        *is_a_team_name = true;
        i++;
    }
    return EXIT_WITH_SUCCESS;
}
