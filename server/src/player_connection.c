/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** player_connection
*/

#include <string.h>
#include "server.h"
#include "command.h"

static unsigned int count_eggs_remaining(const server_t *server,
    const zappy_t *zappy)
{
    unsigned int count_eggs = 0;
    player_t *player = NULL;

    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (strcmp(server->cmd_arg_array[0], player->team_name) == 0 &&
            player->status != IS_PLAYER) {
            count_eggs++;
        }
    }
    return count_eggs;
}

int connect_player(server_t *server, zappy_t *zappy, const arguments_t arg,
    const unsigned int client_fd)
{
    unsigned int count_eggs = 0;
    player_t *player = NULL;

    if (is_player_connected(zappy, client_fd))
        return UNKNOWN_COMMAND;
    for ((player) = ((&zappy->player_head)->tqh_first); (player);
        (player) = ((player)->player_entries.tqe_next)) {
        if (strcmp(server->cmd_arg_array[0], player->team_name) == 0 &&
            player->status != IS_PLAYER) {
            player->id = client_fd;
            player->status = IS_PLAYER;
            player->clock_begin = clock();
            count_eggs = count_eggs_remaining(server, zappy);
            dprintf(client_fd, "%d %d\n%d\n", arg.height, arg.width,
                count_eggs);
            return COMMAND_SUCCESS;
        }
    }
    return UNKNOWN_COMMAND;
}

bool is_player_connected(const zappy_t *zappy, const unsigned int client_fd)
{
    player_t *player = NULL;

    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (player->id == client_fd)
            return true;
    }
    return false;
}
