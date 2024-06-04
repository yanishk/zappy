/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** take_deraumere
*/

#include "command.h"

bool take_deraumere(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp(DERAUMERE, server->cmd_arg_array[1]) == 0
        && zappy->resource[player->height][player->width].deraumere > 0) {
            zappy->resource[player->height][player->width].deraumere -= 1;
            player->inventory.deraumere += 1;
            was_taken = true;
    }
    return was_taken;
}
