/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_tna
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(tna_func, print_game_teams)
{
    arguments_t arg;
    client_t client;
    team_t *team = NULL;
    int res = 0;

    client.client_fd = 0;
    TAILQ_INIT(&arg.team_head);
    team = malloc(sizeof(team_t));
    TAILQ_INSERT_TAIL(&arg.team_head, team, team_entries);
    team->team_name = strdup("team1");

    res = tna_func(NULL, NULL, &arg, &client);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}
