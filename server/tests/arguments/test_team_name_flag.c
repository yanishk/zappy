/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_team_name_flag
*/

#include <criterion/criterion.h>
#include "server.h"

Test(team_name_flag, valid_team)
{
    arguments_t arg;
    team_t *team = NULL;
    char **array = word_array("-n team1", " ");
    char *first_team_name = "team1";
    int nb_team = 1;
    int arg_nb = array_size(array);
    int i = 0;
    int res = 0;

    arg.nb_teams = 0;
    TAILQ_INIT(&arg.team_head);
    res = team_name_flag(arg_nb, (const char **) array, &i, &arg);
    team = TAILQ_FIRST(&arg.team_head);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
    cr_assert_eq(arg.nb_teams, nb_team);
    cr_assert(strcmp(team->team_name, first_team_name) == 0);
}

Test(team_name_flag, valid_team_with_other_flag)
{
    arguments_t arg;
    team_t *team = NULL;
    char **array = word_array("-n team2 -f 10", " ");
    char *first_team_name = "team2";
    int nb_team = 1;
    int arg_nb = 4;
    int i = 0;
    int res = 0;

    arg.nb_teams = 0;
    TAILQ_INIT(&arg.team_head);
    res = team_name_flag(arg_nb, (const char **) array, &i, &arg);
    team = TAILQ_FIRST(&arg.team_head);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
    cr_assert_eq(arg.nb_teams, nb_team);
    cr_assert(strcmp(team->team_name, first_team_name) == 0);
}
