/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** team_name_flag
*/

#include "server.h"

int team_name_flag(const char **, int *i, bool *is_a_team_name, arguments_t *)
{
    *is_a_team_name = true;
    *i += 1;
    return EXIT_WITH_SUCCESS;
}
