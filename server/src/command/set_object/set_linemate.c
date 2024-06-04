/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** set_linemate
*/

#include "server.h"

bool set_linemate(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp(LINEMATE, server->cmd_arg_array[1]) == 0
        && player->inventory.linemate > 0) {
            player->inventory.linemate -= 1;
            zappy->resource[player->height][player->width].linemate += 1;
            was_set = true;
    }
    return was_set;
}
