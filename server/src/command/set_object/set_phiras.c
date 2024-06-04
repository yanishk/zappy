/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** set_phiras
*/

#include "server.h"

bool set_phiras(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp("phiras", server->cmd_arg_array[1]) == 0
    && player->inventory.phiras > 0) {
        player->inventory.phiras -= 1;
        zappy->resource[player->height][player->width].phiras += 1;
        was_set = true;
    }
    return was_set;
}
