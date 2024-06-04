/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** set_deraumere
*/

#include "server.h"

bool set_deraumere(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp("deraumere", server->cmd_arg_array[1]) == 0
        && player->inventory.deraumere > 0) {
            player->inventory.deraumere -= 1;
            zappy->resource[player->height][player->width].deraumere += 1;
            was_set = true;
    }
    return was_set;
}
