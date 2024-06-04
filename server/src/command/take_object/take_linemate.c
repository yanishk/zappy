/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** take_linemate
*/

#include "command.h"

bool take_linemate(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp(LINEMATE, server->cmd_arg_array[1]) == 0
        && zappy->resource[player->height][player->width].linemate > 0) {
            zappy->resource[player->height][player->width].linemate -= 1;
            player->inventory.linemate += 1;
            was_taken = true;
    }
    return was_taken;
}
