/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** set_thystame
*/

#include "server.h"

bool set_thystame(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp(THYSTAME, server->cmd_arg_array[1]) == 0
    && player->inventory.thystame > 0) {
        player->inventory.thystame -= 1;
        zappy->resource[player->height][player->width].thystame += 1;
        was_set = true;
    }
    return was_set;
}
