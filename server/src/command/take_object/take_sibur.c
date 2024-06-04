/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** take_sibur
*/

#include "command.h"

bool take_sibur(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp(DERAUMERE, server->cmd_arg_array[1]) == 0
    && zappy->resource[player->height][player->width].sibur > 0) {
        zappy->resource[player->height][player->width].sibur -= 1;
        player->inventory.sibur += 1;
        was_taken = true;
    }
    return was_taken;
}
