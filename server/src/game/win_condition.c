/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** win_condition
*/

#include "command_gui.h"

static void close_all_client(server_t *server, zappy_t *zappy)
{
    player_t *player = NULL;
    client_t *client = NULL;
    int client_fd = 0;

    for ((player) = ((&zappy->player_head)->tqh_first); (player);
        (player) = ((player)->player_entries.tqe_next)) {
        client_fd = get_client_fd(zappy, player->id);
        client = get_client_in_struct(server, client_fd);
        client->has_been_closed = true;
    }
}

static char *loop_winner(zappy_t *zappy, char *team_name)
{
    player_t *player = NULL;
    int count_winner = 0;

    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (strcmp(player->team_name, team_name) == 0
            && player->level == WIN_LEVEL)
            count_winner += 1;
    }
    if (count_winner >= REQUIRED_WINNER)
        return team_name;
    return NULL;
}

char *win_condition(server_t *server, zappy_t *zappy, arguments_t *arg)
{
    team_t *team = NULL;
    char *winner_team = NULL;

    TAILQ_FOREACH(team, &arg->team_head, team_entries) {
        winner_team = loop_winner(zappy, team->team_name);
        if (winner_team != NULL) {
            seg_func(server, winner_team);
            close_all_client(server, zappy);
            return winner_team;
        }
    }
    return NULL;
}
