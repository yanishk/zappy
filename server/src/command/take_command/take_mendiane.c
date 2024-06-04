/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** take_mendiane
*/

#include "command.h"

bool take_mendiane(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp("mendiane", server->cmd_arg_array[1]) == 0
    && zappy->resource[player->height][player->width].mendiane > 0) {
        zappy->resource[player->height][player->width].mendiane -= 1;
        player->inventory.mendiane += 1;
        was_taken = true;
    }
    return was_taken;
}
