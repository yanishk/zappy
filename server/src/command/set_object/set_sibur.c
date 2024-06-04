/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** set_sibur
*/

#include "server.h"

bool set_sibur(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp(DERAUMERE, server->cmd_arg_array[1]) == 0
    && player->inventory.sibur > 0) {
        player->inventory.sibur -= 1;
        zappy->resource[player->height][player->width].sibur += 1;
        was_set = true;
    }
    return was_set;
}
