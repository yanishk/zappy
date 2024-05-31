/*
** EPITECH PROJECT, 2024
** all_teams
** File description:
** call_cmd_function
*/

#include <string.h>
#include "server.h"

static unsigned int count_active_players(const server_t *server,
    const zappy_t *zappy)
{
    unsigned int count_eggs = 0;
    player_t *player;

    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (strcmp(server->cmd_arg.tab[0], player->team_name) == 0 &&
            !player->is_egg) {
            count_eggs++;
        }
    }
    return count_eggs;
}

int connect_player(server_t *server, zappy_t *zappy, const arguments_t arg,
    const unsigned int client_fd)
{
    unsigned int active_players = 0;
    player_t *player;

    for ((player) = ((&zappy->player_head)->tqh_first); (player);
        (player) = ((player)->player_entries.tqe_next)) {
        if (strcmp(server->cmd_arg.tab[0], player->team_name) == 0 &&
            player->is_egg) {
            player->id = client_fd;
            player->is_egg = false;
            active_players = count_active_players(server, zappy);
            dprintf(client_fd, "%d %d\n%d\n", arg.height, arg.width,
                arg.nb_clients - active_players);
            return EXIT_WITH_SUCCESS;
        }
    }
    return UNKNOWN_COMMAND;
}

bool is_player_connected(const zappy_t *zappy, const unsigned int client_fd)
{
    player_t *player;

    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (player->id == client_fd)
            return true;
    }
    return false;
}
