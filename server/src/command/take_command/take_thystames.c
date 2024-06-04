/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** take_thystames
*/

#include "command.h"

bool take_thystame(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp("thystame", server->cmd_arg_array[1]) == 0
    && zappy->resource[player->height][player->width].thystame > 0) {
        zappy->resource[player->height][player->width].thystame -= 1;
        player->inventory.thystame += 1;
        was_taken = true;
    }
    return was_taken;
}
