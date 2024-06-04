/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** set_mendiane
*/

#include "server.h"

bool set_mendiane(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp("mendiane", server->cmd_arg_array[1]) == 0
    && player->inventory.mendiane > 0) {
        player->inventory.mendiane -= 1;
        zappy->resource[player->height][player->width].mendiane += 1;
        was_set = true;
    }
    return was_set;
}
