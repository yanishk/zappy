/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** win_condition
*/

#include "server.h"
#include "command_gui.h"


void close_all_client(server_t *server, zappy_t *zappy)
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

char *win_condition(server_t *server, zappy_t *zappy)
{
    player_t *player = NULL;

    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (player->level == WIN_LEVEL) {
            seg_func(server, player->team_name);
            close_all_client(server, zappy);
            return player->team_name;
        }
    }
    return NULL;
}
