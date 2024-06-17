/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** team_name_flag
*/

#include "server.h"

static void add_new_team(const char *team_name, arguments_t *arg)
{
    team_t *team = malloc(sizeof(team_t));

    if (team == NULL)
        return;
    TAILQ_INSERT_TAIL(&arg->team_head, team, team_entries);
    team->team_name = strdup(team_name);
    (*arg).nb_teams++;
}

static bool is_a_flag(const char **av, int *i)
{
    for (size_t j = 0; j < NB_FLAGS; j++) {
        if (strcmp(flags[j].name, av[*i]) == 0) {
            *i -= 1;
            return true;
        }
    }
    return false;
}

int team_name_flag(int ac, const char **av, int *i, arguments_t *arg)
{
    *i += 1;
    while (*i < ac) {
        if (is_a_flag(av, i))
            return EXIT_WITH_SUCCESS;
        add_new_team(av[*i], arg);
        *i += 1;
    }
    return EXIT_WITH_SUCCESS;
}
