/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** take_phiras
*/

#include "command.h"

bool take_phiras(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp(PHIRAS, server->cmd_arg_array[1]) == 0
    && zappy->resource[player->height][player->width].phiras > 0) {
        zappy->resource[player->height][player->width].phiras -= 1;
        player->inventory.phiras += 1;
        was_taken = true;
    }
    return was_taken;
}
